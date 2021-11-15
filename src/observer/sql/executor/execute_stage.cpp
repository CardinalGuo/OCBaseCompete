/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Longda on 2021/4/13.
//

#include <string>
#include <sstream>
#include <vector>

#include "execute_stage.h"

#include "common/io/io.h"
#include "common/log/log.h"
#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "event/execution_plan_event.h"
#include "sql/executor/execution_node.h"
#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/default/default_storage_stage.h"
#include "storage/trx/trx.h"
#include "storage/common/check_trans.h"
#include "sql/executor/select_exe.h"

using namespace common;

RC create_selection_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node);

//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag) {}

//! Destructor
ExecuteStage::~ExecuteStage() {}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag)
{
  ExecuteStage *stage = new (std::nothrow) ExecuteStage(tag.c_str());
  if (stage == nullptr)
  {
    LOG_ERROR("new ExecuteStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties()
{
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize()
{
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  default_storage_stage_ = *(stgp++);
  mem_storage_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup()
{
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event)
{
  LOG_TRACE("Enter\n");

  handle_request(event);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context)
{
  LOG_TRACE("Enter\n");

  // here finish read all data from disk or network, but do nothing here.
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SQLStageEvent *sql_event = exe_event->sql_event();
  sql_event->done_immediate();

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::handle_request(common::StageEvent *event)
{
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SessionEvent *session_event = exe_event->sql_event()->session_event();
  Query *sql = exe_event->sqls();
  const char *current_db = session_event->get_client()->session->get_current_db().c_str();

  CompletionCallback *cb = new (std::nothrow) CompletionCallback(this, nullptr);
  if (cb == nullptr)
  {
    LOG_ERROR("Failed to new callback for ExecutionPlanEvent");
    exe_event->done_immediate();
    return;
  }
  exe_event->push_callback(cb);

  switch (sql->flag)
  {
  case SCF_SELECT:
  { // select
    do_select(current_db, sql, session_event);

    exe_event->done_immediate();
  }
  break;

  case SCF_INSERT:
  case SCF_UPDATE:
  case SCF_DELETE:
  case SCF_CREATE_TABLE:
  case SCF_SHOW_TABLES:
  case SCF_DESC_TABLE:
  case SCF_DROP_TABLE:
  case SCF_CREATE_INDEX:
  case SCF_DROP_INDEX:
  case SCF_LOAD_DATA:
  {
    StorageEvent *storage_event = new (std::nothrow) StorageEvent(exe_event);
    if (storage_event == nullptr)
    {
      LOG_ERROR("Failed to new StorageEvent");
      event->done_immediate();
      return;
    }

    default_storage_stage_->handle_event(storage_event);
  }
  break;
  case SCF_SYNC:
  {
    RC rc = DefaultHandler::get_default().sync();
    session_event->set_response(strrc(rc));
    exe_event->done_immediate();
  }
  break;
  case SCF_BEGIN:
  {
    session_event->get_client()->session->set_trx_multi_operation_mode(true);
    session_event->set_response(strrc(RC::SUCCESS));
    exe_event->done_immediate();
  }
  break;
  case SCF_COMMIT:
  {
    Trx *trx = session_event->get_client()->session->current_trx();
    RC rc = trx->commit();
    session_event->get_client()->session->set_trx_multi_operation_mode(false);
    session_event->set_response(strrc(rc));
    exe_event->done_immediate();
  }
  break;
  case SCF_ROLLBACK:
  {
    Trx *trx = session_event->get_client()->session->current_trx();
    RC rc = trx->rollback();
    session_event->get_client()->session->set_trx_multi_operation_mode(false);
    session_event->set_response(strrc(rc));
    exe_event->done_immediate();
  }
  break;
  case SCF_HELP:
  {
    const char *response = "show tables;\n"
                           "desc `table name`;\n"
                           "create table `table name` (`column name` `column type`, ...);\n"
                           "create index `index name` on `table` (`column`);\n"
                           "insert into `table` values(`value1`,`value2`);\n"
                           "update `table` set column=value [where `column`=`value`];\n"
                           "delete from `table` [where `column`=`value`];\n"
                           "select [ * | `columns` ] from `table`;\n";
    session_event->set_response(response);
    exe_event->done_immediate();
  }
  break;
  case SCF_EXIT:
  {
    // do nothing
    const char *response = "Unsupported\n";
    session_event->set_response(response);
    exe_event->done_immediate();
  }
  break;
  default:
  {
    exe_event->done_immediate();
    LOG_ERROR("Unsupported command=%d\n", sql->flag);
  }
  }

  //query_destroy(sql);
}

void end_trx_if_need(Session *session, Trx *trx, bool all_right)
{
  if (!session->is_trx_multi_operation_mode())
  {
    if (all_right)
    {
      trx->commit();
    }
    else
    {
      trx->rollback();
    }
  }
}

// RC ExecuteStage::check_attri_valid(RelAttr attr, Selects selects, Db *db){
//   bool exist = false;
//   //LOG_INFO("check_attri");
//   if (attr.relation_name == nullptr){
//     //LOG_INFO("check_ nullptr");
//     for (size_t i = 0; i < selects.relation_num; i++){
//       Table *table = db->find_table(selects.relations[i]);
//       if (strcmp(attr.attribute_name, "*") == 0 ) return RC::SUCCESS;
//       const FieldMeta* fieldmeta = table->table_meta().field(attr.attribute_name);
//       if (fieldmeta != nullptr){
//         exist = true;
//         break;
//       }
//     }
//   }else{
//     //LOG_INFO("check_attri rela");
//     for (size_t i = 0; i < selects.relation_num; i++){
//       if (0 == strcmp(attr.relation_name, selects.relations[i])){
//         Table *table = db->find_table(selects.relations[i]);
//         if (strcmp(attr.attribute_name, "*") == 0 ) return RC::SUCCESS;
//         const FieldMeta* fieldmeta = table->table_meta().field(attr.attribute_name);
//         if (fieldmeta != nullptr){
//           exist = true;
//           break;
//         }
//       }
//     }
//   }

//   if (!exist) return RC::INVALID_ARGUMENT;
//   return RC::SUCCESS;
// }
// RC ExecuteStage::check_condition_value_equal(Condition condition,char *relations[MAX_NUM], size_t relation_num, Db *db){
//   AttrType tp_left = UNDEFINED, tp_right = UNDEFINED;
//   if (condition.left_is_attr) {
//     for (size_t i = 0; i < relation_num; i++){
//       Table *table = db->find_table(relations[i]);
//       const FieldMeta* fieldmeta = table->table_meta().field(condition.left_attr.attribute_name);
//       if (fieldmeta != nullptr){
//         LOG_INFO("%s",fieldmeta->name());
//         tp_left = fieldmeta->type();
//       }
//     }
//   }else{
//     tp_left = condition.left_value.type;
//   }

//   if (condition.right_is_attr) {
//     for (size_t i = 0; i < relation_num; i++){
//       Table *table = db->find_table(relations[i]);
//       const FieldMeta* fieldmeta = table->table_meta().field(condition.right_attr.attribute_name);
//       if (fieldmeta != nullptr){

//         tp_right = fieldmeta->type();
//       }
//     }
//   }else{
//     tp_right = condition.right_value.type;
//   }

//   if ((tp_left == DATES) && !condition.right_is_attr){
//     //LOG_INFO("%d",tp_left);
//     if(!check_trans::check_date( (char *)condition.right_value.data)) return RC::INVALID_ARGUMENT;
//   }
//   if ((tp_right == DATES) && !condition.left_is_attr){
//     //LOG_INFO("%d",tp_right);
//     if(!check_trans::check_date( (char *)condition.left_value.data)) return RC::INVALID_ARGUMENT;
//   }

//   //ATTENTION 没有对字符串比较行为做筛选
//   if ((tp_left == CHARS && tp_right == DATES )|| (tp_left == DATES && tp_right == CHARS)) return RC::SUCCESS;
//   return ((tp_left == tp_right) ? RC::SUCCESS : RC::INVALID_ARGUMENT);
// }

// RC ExecuteStage::check_condition_valid(Condition condition, Selects selects, Db *db){

//   if (condition.left_is_attr) {
//     RC rc = check_attri_valid(condition.left_attr, selects, db);
//     if (rc != SUCCESS) return RC::INVALID_ARGUMENT;
//   }

//   if (condition.right_is_attr) {
//     RC rc = check_attri_valid(condition.right_attr, selects, db);
//     if (rc != SUCCESS) return RC::INVALID_ARGUMENT;
//   }

//   RC rc = check_condition_value_equal(condition, selects.relations, selects.relation_num, db);
//   if (rc != SUCCESS) return RC::INVALID_ARGUMENT;

//   return RC::SUCCESS;
// }
// RC ExecuteStage::check_aggrevage_valid(RelAttr attr, Selects selects, Db *db){
//   RC rc = RC::SUCCESS;
//   Table *table;
//   if (attr.relation_name == nullptr){
//     for (size_t i = 0; i < selects.relation_num; i++){
//       //LOG_INFO("check aggra %s %s", attr.relation_name, selects.relations[i]);
//       Table *table_tmp = db->find_table(selects.relations[i]);
//       const FieldMeta* fieldmeta = table_tmp->table_meta().field(attr.attribute_name);
//       if (fieldmeta != nullptr){
//         table = table_tmp;
//         break;
//       }
//     }
//   }else{
//     for (size_t i = 0; i < selects.relation_num; i++){
//       //LOG_INFO("check aggra %s %s", attr.relation_name, selects.relations[i]);
//       if (0 == strcmp(attr.relation_name, selects.relations[i])){
//         table = db->find_table(selects.relations[i]);
//         break;
//       }
//     }
//   }
//   const FieldMeta* fieldmeta = table->table_meta().field(attr.attribute_name);
//   AttrType type = fieldmeta->type();
//   if (strcmp("MAX",attr.extra_attribute_name)==0 || strcmp("MIN",attr.extra_attribute_name)==0){
//     if (type == CHARS) rc = RC::INVALID_ARGUMENT;
//   }else if(strcmp("AVG",attr.extra_attribute_name)==0){
//     if (type == CHARS || type == DATES) rc = RC::INVALID_ARGUMENT;
//   }
//   //LOG_INFO("check aggra ok");
//   return rc;
// }

//flag = 1 table_size = 1
// void insert_field_from_table(std::unordered_map<std::string, AttrType> &field_set, Table *table, int flag){
//   const char *table_name = table->name();
//   //LOG_INFO("%s",table_name);
//   const TableMeta &table_meta = table->table_meta();
//   const int field_num = table_meta.field_num();
//   std::string str_name = "";
//   for (int i = 0; i < field_num; i++) {
//     const FieldMeta *field_meta = table_meta.field(i);
//     if (field_meta->visible()) {
//       str_name = "";
//       str_name.append(table_name).append(".").append(field_meta->name());
//       field_set[str_name] = field_meta->type();
//       //LOG_INFO("%s",str_name.c_str());
//       if (flag){
//         str_name = "";
//         str_name.append(field_meta->name());
//         field_set[str_name] = field_meta->type();

//       }
//     }
//   }
//   str_name = "";
//   str_name.append(table_name).append(".").append("*");
//   field_set[str_name] = UNDEFINED;
//   str_name = "*";
//   field_set[str_name] = UNDEFINED;
// }

// RC check_expression(std::unordered_map<std::string, AttrType> &field_set, Expression *expression){
//   if (expression->is_leaf == 1){
//     if (expression->is_attr){
//       std::string str_name = "";
//       const RelAttr *relattr = &expression->attr;
//       if (relattr->relation_name != nullptr) str_name.append(relattr->relation_name).append(".");
//       str_name.append(relattr->attribute_name);
//       if (field_set.find(str_name) == field_set.end()) return RC::INVALID_ARGUMENT;
//     }
//   }else{
//     RC rc_left = expression->left == nullptr ? RC::SUCCESS : check_expression(field_set,expression->left);
//     if (rc_left != RC::SUCCESS) return RC::INVALID_ARGUMENT;
//     RC rc_right = expression->right == nullptr ? RC::SUCCESS : check_expression(field_set,expression->right);
//     if (rc_right != RC::SUCCESS) return RC::INVALID_ARGUMENT;
//   }
//   return RC::SUCCESS;
// }

// RC ExecuteStage::check_condition_valid(Condition_Composite *condition, std::unordered_map<std::string, AttrType> &field_set, Db *datebase){
//   RC rc = RC::SUCCESS;
//   if (condition->left != nullptr) rc = check_expression(field_set, condition->left);
//   if (rc != SUCCESS) return RC::INVALID_ARGUMENT;
//   if (condition->right != nullptr) rc = check_expression(field_set, condition->right);
//   if (rc != SUCCESS) return RC::INVALID_ARGUMENT;
//   if (condition->select_attr_in != nullptr) rc = check_select(*(Selects*)condition->select_attr_in, datebase);
//   if (rc != SUCCESS) return RC::INVALID_ARGUMENT;
//   return RC::SUCCESS;
// }
// RC ExecuteStage::check_join(std::unordered_map<std::string, AttrType> field_set,const JoinOn *joinon, Db *datebase){
//   RC rc = RC::SUCCESS;
//   for (size_t i = 0; i < joinon->condition_num ; i++){
//     Condition_Composite *condition = joinon->conditions[i];
//     rc = check_condition_valid(condition, field_set, datebase);
//     if (rc != SUCCESS) return RC::INVALID_ARGUMENT;
//   }
//   return RC::SUCCESS;
// }
// RC ExecuteStage::check_select(const Selects selects, Db *datebase){

//   RC rc = RC::SUCCESS;

//   LOG_INFO("check table");
//   for (size_t i = 0; i < selects.relation_num; i++){
//     if (nullptr == datebase->find_table(selects.relations[i])) return RC::INVALID_ARGUMENT;
//   }

//   std::unordered_map<std::string, AttrType> field_set;

//   //add_field into map
//   if (selects.relation_num == 1){
//     Table *table = datebase->find_table(selects.relations[0]);
//     insert_field_from_table(field_set,table,1);
//   }else{
//     for (size_t i = 0; i < selects.relation_num; i++){
//       Table *table = datebase->find_table(selects.relations[i]);
//       insert_field_from_table(field_set,table,0);
//     }
//   }

//   LOG_INFO("check_join %d", selects.join_num_max - 1);
//   for (int i = selects.join_num_max - 1; i >= 0; i--){
//     Table *table = datebase->find_table(selects.join_on[i].relation_name);
//     std::string str_name = "";
//     str_name.append(selects.join_on[i].relation_name).append(".").append("*");
//     //LOG_INFO("%s",str_name.c_str());
//     if (field_set.find(str_name) != field_set.end()) return RC::INVALID_ARGUMENT;
//     insert_field_from_table(field_set,table,0);
//     rc = check_join(field_set, &selects.join_on[i],datebase);
//     if (rc != SUCCESS) return RC::INVALID_ARGUMENT;
//   }

//   // for (auto it : field_set){
//   //   LOG_INFO("%s",it.first.c_str());
//   // }

//   LOG_INFO("check show_select");
//   for (size_t i = 0; i < selects.expression_select_num; i++){
//     Expression *expre_tmp = selects.expression_select[i];
//     rc = check_expression(field_set, expre_tmp);
//     if (rc != SUCCESS) return RC::INVALID_ARGUMENT;
//   }

//   LOG_INFO("check condition %d", selects.condition_num);
//   for (size_t i = 0; i < selects.condition_num ; i++){
//     Condition_Composite *condition = selects.conditions[i];
//     rc = check_condition_valid(condition, field_set, datebase);
//     if (rc != SUCCESS) return RC::INVALID_ARGUMENT;
//   }

//   LOG_INFO("check group");
//   const GroupBy *groupby = &selects.group_by;
//   for (size_t i = 0;i < groupby->attr_num;i++){
//     const RelAttr *relattr = &groupby->attributes[i];
//     std::string str_name = "";
//     if (relattr->relation_name != nullptr) str_name.append(relattr->relation_name).append(".");
//     str_name.append(relattr->attribute_name);
//     if (field_set.find(str_name) == field_set.end()) return RC::INVALID_ARGUMENT;
//   }

//   LOG_INFO("check order");
//   const OrderBy *orderby = &selects.order_by;
//   for (size_t i = 0;i < orderby->attr_num;i++){
//     const RelAttr *relattr = &orderby->attributes[i];
//     std::string str_name = "";
//     if (relattr->relation_name != nullptr) str_name.append(relattr->relation_name).append(".");
//     str_name.append(relattr->attribute_name);
//     if (field_set.find(str_name) == field_set.end()) return RC::INVALID_ARGUMENT;
//   }

//   return rc;
// }

// void combain_tables_record(std::vector<int> &index_vec, std::vector<TupleSet> &tuplesets, TupleSet &tupleset_out, const Selects selects, std::map<std::string, int> schema_map){
//   Tuple tuple;
//   for (int i = 0;i < tuplesets.size();i++){
//     const std::vector<std::shared_ptr<TupleValue>> values = tuplesets[i].get(index_vec[i]).values();
//     for (auto it : values){
//       tuple.add(it);
//     }
//   }
//   index_vec[0]++;
//   std::vector<std::shared_ptr<TupleValue>> values = tuple.values();
//   bool is_suffient = true;
//   for (size_t i = 0; i < selects.condition_num;i++){
//     if (!is_suffient) break;
//     Condition condition_tmp = selects.conditions[i];
//     if (condition_tmp.left_is_attr && condition_tmp.right_is_attr){
//       std::string name_left = condition_tmp.left_attr.relation_name;
//       name_left.append(".").append(condition_tmp.left_attr.attribute_name);
//       int index_left = schema_map[name_left];
//       std::string name_right = condition_tmp.right_attr.relation_name;
//       name_right.append(".").append(condition_tmp.right_attr.attribute_name);
//       int index_right = schema_map[name_right];
//       //LOG_INFO("doing compare");
//       int cmp_result = values[index_left]->compare(*values[index_right]);

//       switch (condition_tmp.comp) {
//         case EQUAL_TO:
//           is_suffient = (0 == cmp_result);
//           break;
//         case LESS_EQUAL:
//           is_suffient = (cmp_result <= 0);
//           break;
//         case NOT_EQUAL:
//           is_suffient = (cmp_result != 0);
//           break;
//         case LESS_THAN:
//           is_suffient = (cmp_result < 0);
//           break;
//         case GREAT_EQUAL:
//           is_suffient = (cmp_result >= 0);
//           break;
//         case GREAT_THAN:
//           is_suffient = (cmp_result > 0);
//           break;
//         default:
//           break;
//       }
//     }
//   }
//   if (is_suffient) tupleset_out.add(std::move(tuple));
// }

// void swap_delete_tupleset(TupleSet &tupleset_out, std::map<std::string, int> &schema_map, const Selects selects){

// }

// TupleSet ExecuteStage::combain_by_condition(int sets_size, std::vector<TupleSet> &tuplesets, const Selects selects){
//   TupleSet tupleset_out;
//   TupleSchema schema_out;
//   std::map<std::string, int> schema_map;
//   std::map<std::string, int> schema_map_out;

//   int schema_num = 0;
//   for (int i = 0;i < sets_size;i++){
//     TupleSchema schema_tmp = tuplesets[i].get_schema();
//     size_t fields_size = schema_tmp.fields().size();
//     for (size_t j = 0; j < fields_size; j++){
//       //LOG_INFO("%s %s",schema_tmp.field(j).table_name(),schema_tmp.field(j).field_name());

//       if (schema_out.add_if_not_exists_return(schema_tmp.field(j).type(), schema_tmp.field(j).table_name(), schema_tmp.field(j).field_name(), schema_tmp.field(j).calcu_name())){
//         std::string str = schema_tmp.field(j).table_name();
//         str.append(".").append(schema_tmp.field(j).field_name());
//         schema_map[str] = schema_num;
//         schema_num++;
//       }
//     }
//   }

//   std::vector<int> index_vec, max_size_vec;
//   int tmp_sum = 0, max_sum = 1;
//   for (int i = 0; i < sets_size ; i++) {
//     index_vec.push_back(0);
//     max_sum *= tuplesets[i].size();
//     max_size_vec.push_back(tuplesets[i].size() - 1);
//   }

//   while (tmp_sum != max_sum){
//     tmp_sum++;
//     combain_tables_record(index_vec, tuplesets, tupleset_out, selects, schema_map);
//     int index = 0;

//     while((index_vec[index]-1) == max_size_vec[index] && index < sets_size - 1){
//       index_vec[index++] = 0;
//       index_vec[index]++;
//     }
//   }

//   swap_delete_tupleset(tupleset_out, schema_map, selects);

//   tupleset_out.set_schema(schema_out);
//   return tupleset_out;
// }

// void do_group_by(std::vector<std::string> &records,Selects &selects, std::map<std::string, int> &offset_map){

// // }
// typedef struct Schema_Info{
//   int offset;                 //找到offset
//   int len;                    //读多长
//   AttrType type;              //转化为什么类型
// }Schema_Info;

// void do_order_by(std::vector<char *> &records,Selects &selects, std::unordered_map<std::string, Schema_Info> &table_map){
//   OrderBy *orderby = &selects.order_by;
//   std::sort(records.begin(), records.end(),[orderby, table_map](char *left,char *right){
//     // int left_null = 1;
//     // int right_null = 1;
//     // char *left_value = left.c_str();
//     // char *right_value = left.c_str();
//     // if (0 == strcmp(left_value, "GAY")) left_null = 0;
//     // if (0 == strcmp(right_value, "GAY")) right_null = 0;

//     // if (left_null || right_null) return (left_null - right_null)
//     std::string name;
//     for (int i = 0;i < orderby->attr_num; i++){
//       if(orderby->attributes[i].relation_name != nullptr) name.append(orderby->attributes[i].relation_name).append(".");
//       name.append(orderby->attributes[i].attribute_name);

//       //LOG_INFO("%s", name.c_str());
//       Schema_Info schema_tmp = table_map.find(name)->second;
//       int attr_offset = schema_tmp.offset;
//       AttrType type_tmp = schema_tmp.type;

//       //LOG_INFO("%d %d",attr_offset, type_tmp);
//       char *left_value = left + attr_offset;
//       char *right_value = right + attr_offset;

//       switch (type_tmp)
//       {
//       case INTS:{
//         int left_val = *(int*)left_value;
//         int right_val = *(int*)right_value;
//         if (left_val != right_val) return orderby->up_or_down[i] == 1 ? left_val > right_val : left_val < right_val ;
//         break;
//       }
//       case FLOATS:{
//         float left_val = *(float*)left_value;
//         float right_val = *(float*)right_value;
//         if (left_val != right_val) return orderby->up_or_down[i] == 1 ? left_val > right_val : left_val < right_val ;
//         break;
//       }
//       case DATES:{
//         int compare_result = strcmp(left_value,right_value);
//         if (compare_result != 0) return orderby->up_or_down[i] == 1 ? compare_result > 0 : compare_result < 0 ;
//         break;
//       }
//       case CHARS:{
//         break;
//       }
//       default:
//         break;
//       }
//     }
//     return true;
//   });
// }

// 这里没有对输入的某些信息做合法性校验，比如查询的列名、where条件中的列名等，没有做必要的合法性校验
// 需要补充上这一部分. 校验部分也可以放在resolve，不过跟execution放一起也没有关系
RC ExecuteStage::do_select(const char *db, Query *sql, SessionEvent *session_event)
{

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  Selects &selects = sql->sstr.selection[0];

  //show_selects(selects);
  DefaultStorageStage *h = (DefaultStorageStage *)default_storage_stage_;
  DefaultHandler *dh = h->handler();
  Db *datebase = dh->find_db(db);

  SelectExe select_exe = SelectExe();
  select_exe.SelectExe_init(datebase, selects, trx);

  std::vector<std::vector<void *>> select_ress;
  std::vector<std::string> select_res_fields;
  std::vector<AttrType> types;

  rc = select_exe.terminal_select(select_ress, types, select_res_fields);

  LOG_INFO("cal sum res");
  int sum = 0;
  for (auto it : select_ress)
  {
    for (auto jt : it)
    {
      LOG_INFO("data %d %d", sum++, *(int *)jt);
    }
  }
  if (rc != SUCCESS)
  {
    session_event->set_response("FAILURE\n");
    return rc;
  }
  LOG_INFO("out stream field");
  std::stringstream ss;

  for (int i = 0; i < select_res_fields.size(); i++)
  {
    ss << select_res_fields[i];
    if (i != select_res_fields.size() - 1)
      ss << "  |  ";
  }
  ss << std::endl;
  LOG_INFO("out stream ress %d", (int)select_ress.size());

  if (select_ress.size() != 0)
  {
    int size = select_ress[0].size();
    for (int i = 0; i < select_ress.size(); i++)
    {
      if (select_ress[i].size() < size)
      {
        size = (int)select_ress[i].size();
      }
    }
    LOG_INFO("size %d %d", (int)select_ress.size(), (int)select_ress[0].size());
    for (int i = 0; i < size; i++)
    {
      for (int j = 0; j < select_ress.size(); j++)
      {
        switch (types[j])
        {
        case INTS:
        {
          int tmp_int = *(int *)(select_ress[j][i]);

          ss << tmp_int << " ";
        }
        break;
        case FLOATS:
        {
          float tmp_float = *(float *)select_ress[j][i];
          tmp_float = round(tmp_float * 100) / 100.0;
          ss << tmp_float << " ";
        }
        break;
        case DATES:
        {
          int tmp_int = *(int *)(select_ress[j][i]);
          std::string date = std::to_string(tmp_int);
          date.insert(6,"-");
          date.insert(4,"-");
          ss << date << " ";
        }
        break;
        case CHARS:
        {
          const char *str = (char *)select_ress[j][i];
          ss << str << " ";
        }
        break;
        default:
          break;
        }
        free(select_ress[j][i]);
        if (j != select_ress.size() - 1)
          ss << "| " ;
      }
      
      ss << std::endl;
    }
  }

  session_event->set_response(ss.str());
  end_trx_if_need(session, trx, true);

  //relation add map

  //join 1.add relation_schame map, 2. combain record and filter 3. select . where

  //none join combain and filter

  // select_exe.combain_table();

  // select_exe.show_records();

  // if (selects.join_num_max > 0){
  //   for (int i = selects.join_num_max - 1 ;i >= 0; i--){
  //     JoinOn *joinon = &selects.join_on[i];
  //       // select_exe.add_schame_map(joinon->relation_name);
  //       // select_exe.load_records_from_table(joinon->relation_name);

  //       // select_exe.combain_join(joinon);
  //   }
  // }

  // std::vector<std::vector<char *>> tables_records;
  // Table *table = datebase->find_table(selects.relations[0]);
  // std::vector<char *> *vec_records = &select_exe.vec_records;
  // table->scan_record_string(trx, *vec_records);
  // tables_records.push_back(*vec_records);
  // // for (auto it : *vec_records){
  //   char *trx = it + 0;
  //   char *value = it + 4;
  //   char *dd = it + 20;
  //   LOG_INFO("%d %d %d",*trx,*value,*dd);
  // }
  // select_exe.do_order_by(*vec_records,selects);

  // for (auto it : *vec_records){
  //   char *trx = it + 0;
  //   char *value = it + 4;
  //   char *dd = it + 20;
  //   LOG_INFO("%d %d %d",*trx,*value,*dd);
  // }

  // select_exe.do_group_by(*vec_records, selects);

  // int sum = 1;
  // for (auto it : select_exe.group_index_result){
  //   for(auto jt : it){
  //     LOG_INFO("%d %d",sum,jt);
  //   }
  //   sum++;
  // }

  // rc = select_exe.calculate_result(*vec_records, selects);

  // for (size_t i = 0; i < vec_records->size(); i++)
  // {
  //   free((*vec_records)[i]);
  // }

  if (rc != RC::SUCCESS)
  {
    session_event->set_response("FAILURE\n");
    return RC::INVALID_ARGUMENT;
  }
  // std::map<std::string, int> schema_map_out;
  // int schema_num = 0;
  // if (selects.relation_num > 1){
  // for (size_t i = 0; i < selects.attr_num; i++)
  // {
  //   if (0 == strcmp(selects.attributes[i].attribute_name,"*") && 0 == strcmp(selects.attributes[i].extra_attribute_name,"IDEO")){
  //     Table * table = DefaultHandler::get_default().find_table(db, selects.attributes[i].relation_name);
  //     const char *table_name = table->name();
  //     const TableMeta &table_meta = table->table_meta();
  //     const int field_num = table_meta.field_num();

  //     for (int i = 0; i < field_num; i++) {
  //       const FieldMeta *field_meta = table_meta.field(i);
  //       if (field_meta->visible()) {
  //         std::string str = selects.attributes[i].relation_name;
  //         str.append(".").append(field_meta->name());
  //         schema_map_out[str] = schema_num;
  //         schema_num++;
  //       }
  //     }
  //   }else{

  //   }
  // }
  // }

  // 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
  // std::vector<SelectExeNode *> select_nodes;
  // for (size_t i = 0; i < selects.relation_num; i++) {
  //   const char *table_name = selects.relations[i];
  //   SelectExeNode *select_node = new SelectExeNode;
  //   rc = create_selection_executor(trx, selects, db, table_name, *select_node);
  //   if (rc != RC::SUCCESS) {
  //     delete select_node;
  //     for (SelectExeNode *& tmp_node: select_nodes) {
  //       delete tmp_node;
  //     }
  //     end_trx_if_need(session, trx, false);
  //     return rc;
  //   }
  //   select_nodes.push_back(select_node);
  // }

  // if (select_nodes.empty()) {
  //   LOG_ERROR("No table given");
  //   end_trx_if_need(session, trx, false);
  //   return RC::SQL_SYNTAX;
  // }

  // std::vector<TupleSet> tuple_sets;
  // int sets_size = 0;
  // for (SelectExeNode *&node: select_nodes) {
  //   TupleSet tuple_set;
  //   rc = node->execute(tuple_set);
  //   if (rc != RC::SUCCESS) {
  //     for (SelectExeNode *& tmp_node: select_nodes) {
  //       delete tmp_node;
  //     }
  //     end_trx_if_need(session, trx, false);
  //     return rc;
  //   } else {
  //     // TupleSchema ts = tuple_set.schema();
  //     //   for(const auto &field: ts.fields()){
  //     //     LOG_INFO("%s %s %s",field.calcu_name(),field.field_name(),field.table_name());
  //     //     }
  //     //LOG_INFO(" 123123");
  //     tuple_set.check_calculate();
  //     sets_size++;
  //     tuple_sets.push_back(std::move(tuple_set));
  //   }
  // }

  //
  // if (tuple_sets.size() > 1) {
  //   // 本次查询了多张表，需要做join操作
  //   //combain_by_condition(sets_size, tuple_sets, selects).print(ss);
  // } else {
  //   // 当前只查询一张表，直接返回结果即可
  //   tuple_sets.front().print(ss);
  // }

  // for (SelectExeNode *& tmp_node: select_nodes) {
  //   delete tmp_node;
  // }
  return rc;
}

bool match_table(const Selects &selects, const char *table_name_in_condition, const char *table_name_to_match)
{
  if (table_name_in_condition != nullptr)
  {
    return 0 == strcmp(table_name_in_condition, table_name_to_match);
  }

  return selects.relation_num == 1;
}

static RC schema_add_field(Table *table, const char *field_name, TupleSchema &schema, const char *calculate_name)
{
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta && (0 != strcmp(field_name, "COUNT")))
  {
    LOG_INFO("No such field. %s.%s", table->name(), field_name);
    return RC::SCHEMA_FIELD_MISSING;
  }
  if (0 == strcmp(field_name, "COUNT"))
    schema.add_if_not_exists(INTS, table->name(), "__trx", calculate_name);
  schema.add_if_not_exists(field_meta->type(), table->name(), field_meta->name(), calculate_name);
  return RC::SUCCESS;
}

// 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
RC create_selection_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node)
{
  // // 列出跟这张表关联的Attr
  // TupleSchema schema;
  // Table * table = DefaultHandler::get_default().find_table(db, table_name);
  // if (nullptr == table) {
  //   LOG_WARN("No such table [%s] in db [%s]", table_name, db);
  //   return RC::SCHEMA_TABLE_NOT_EXIST;
  // }

  // for (size_t i = 0; i <= selects.attr_num - 1; i++) {
  //   const RelAttr &attr = selects.attributes[i];
  //   if (nullptr == attr.relation_name || 0 == strcmp(table_name, attr.relation_name)) {
  //     if (0 == strcmp("*", attr.attribute_name)) {
  //       // 列出这张表所有字段
  //       TupleSchema::from_table(table, schema);
  //       break; // 没有校验，给出* 之后，再写字段的错误
  //     }else {
  //       // 列出这张表相关字段
  //       RC rc = schema_add_field(table, attr.attribute_name, schema, attr.extra_attribute_name);
  //       if (rc != RC::SUCCESS) {
  //         return rc;
  //       }
  //     }
  //   }
  // }

  // for (size_t i = 0; i < selects.condition_num; i++) {
  //   Condition condition_tmp = selects.conditions[i];
  //   if (condition_tmp.left_is_attr && condition_tmp.right_is_attr){
  //     if (0 != strcmp(condition_tmp.left_attr.relation_name, condition_tmp.right_attr.relation_name)){
  //       //LOG_INFO("%s %s %s %s",condition_tmp.left_attr.relation_name, condition_tmp.left_attr.attribute_name, condition_tmp.right_attr.relation_name, condition_tmp.right_attr.attribute_name);

  //       if (0 == strcmp(condition_tmp.left_attr.relation_name, table_name)){

  //         RC rc = schema_add_field(table, condition_tmp.left_attr.attribute_name, schema, "IDEO");
  //         if (rc != RC::SUCCESS) {
  //           return rc;
  //         }
  //       }

  //       if (0 == strcmp(condition_tmp.right_attr.relation_name, table_name)){
  //         RC rc = schema_add_field(table, condition_tmp.right_attr.attribute_name, schema, "IDEO");
  //         if (rc != RC::SUCCESS) {
  //           return rc;
  //         }
  //       }
  //       //LOG_INFO("%s %s %s %s",condition_tmp.left_attr.relation_name, condition_tmp.left_attr.attribute_name, condition_tmp.right_attr.relation_name, condition_tmp.right_attr.attribute_name);

  //     }
  //   }
  // }
  // //LOG_INFO(")addddd okkk");

  // // 找出仅与此表相关的过滤条件, 或者都是值的过滤条件
  // std::vector<DefaultConditionFilter *> condition_filters;
  // for (size_t i = 0; i < selects.condition_num; i++) {
  //   const Condition &condition = selects.conditions[i];
  //   if ((condition.left_is_attr == 0 && condition.right_is_attr == 0) || // 两边都是值
  //       (condition.left_is_attr == 1 && condition.right_is_attr == 0 && match_table(selects, condition.left_attr.relation_name, table_name)) ||  // 左边是属性右边是值
  //       (condition.left_is_attr == 0 && condition.right_is_attr == 1 && match_table(selects, condition.right_attr.relation_name, table_name)) ||  // 左边是值，右边是属性名
  //       (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
  //           match_table(selects, condition.left_attr.relation_name, table_name) && match_table(selects, condition.right_attr.relation_name, table_name)) // 左右都是属性名，并且表名都符合
  //       ) {
  //     DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
  //     RC rc = condition_filter->init(*table, condition);
  //     if (rc != RC::SUCCESS) {
  //       delete condition_filter;
  //       for (DefaultConditionFilter * &filter : condition_filters) {
  //         delete filter;
  //       }
  //       return rc;
  //     }
  //     condition_filters.push_back(condition_filter);
  //   }
  // }

  //return select_node.init(trx, table, std::move(schema), std::move(condition_filters));
  return RC::SUCCESS;
}
