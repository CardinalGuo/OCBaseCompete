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
#include<iostream>
#include <mutex>
#include "sql/parser/parse.h"
#include "rc.h"
#include "common/log/log.h"

RC parse(char *st, Query *sqln);

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void expression_init_node(Expression *expression, Expression *expression_left, Expression *expression_right, Calculate cal_tmp){
  expression->left = expression_left;
  if (expression_right != NULL) {
    expression->right = expression_right;
  }else{
    expression->right = nullptr;
  }
  expression->is_leaf = 0;
  expression->calculate = cal_tmp;
  //LOG_INFO("exp node init address = %d ", expression);
}
void show_condition(Condition_Composite *condition){
  LOG_INFO("%d" , condition->comp);
  if (condition->left != nullptr) show_expression(condition->left);
  if (condition->right != nullptr) show_expression(condition->right);
  if (condition->select_attr_left != nullptr) show_selects(*(Selects*)condition->select_attr_left);
  if (condition->select_attr_right != nullptr) show_selects(*(Selects*)condition->select_attr_right);
}

void show_select_num(int num){
  LOG_INFO("show select num %d",num);
}


void expression_init_leaf(Expression *expression, Value *value){
  expression->value = *value;
  expression->is_leaf = 1;
  expression->is_attr = 0;
  //LOG_INFO("exp node init address = %d value type %d", expression, expression->value->type);
}
void expression_init_leaf_attr(Expression *expression, RelAttr *attr){
  expression->attr = *attr;
  expression->is_leaf = 1;
  expression->is_attr = 1;
}




void relation_attr_init_extra(RelAttr *relation_attr, const char *relation_name, const char *attribute_name, const char *attribute_name_extra) {
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  relation_attr->extra_attribute_name = strdup(attribute_name_extra);
  relation_attr->attribute_name = strdup(attribute_name);
}

void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name) {
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  relation_attr->attribute_name = strdup(attribute_name);
}

void relation_attr_destroy(RelAttr *relation_attr) {
  free(relation_attr->relation_name);
  free(relation_attr->attribute_name);
  free(relation_attr->extra_attribute_name);
  relation_attr->relation_name = nullptr;
  relation_attr->attribute_name = nullptr;
  relation_attr->extra_attribute_name = nullptr;
}
void record_init_from_values(Value record[], Value values[], size_t length){
  for (size_t i = 0; i < length; i++)
  {
    record[i] = values[i];
  }
}
void value_init_integer(Value *value, int v) {
  value->type = INTS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}

void value_init_NULL(Value *value, const char * v) {
  value->type = NULL_TYPE;
  value->data = strdup(v);
}

void value_init_float(Value *value, float v) {
  value->type = FLOATS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_string(Value *value, const char *v) {

  //LOG_ERROR("here %s",(v));
  value->type = CHARS;
  value->data = strdup(v);
  //LOG_ERROR("here %s",(value->data));
}


void value_destroy(Value *value) {
  value->type = UNDEFINED;
  free(value->data);
  value->data = nullptr;
}

void condition_exp_exp_init(Condition_Composite *condition_composite, Expression *left, Expression *right, CompOp cp){
  condition_composite->left = left;
  condition_composite->right = right;
  condition_composite->select_attr_left = nullptr;
  condition_composite->select_attr_right = nullptr;
  condition_composite->comp = cp;
}
void condition_select_select_init(Condition_Composite *condition_composite, Selects *select_left, Selects *select_right, CompOp cp){
  condition_composite->left = nullptr;
  condition_composite->right = nullptr;
  condition_composite->select_attr_left = (void*)select_left;
  condition_composite->select_attr_right = (void*)select_right;
  condition_composite->comp = cp;
}
void condition_select_exe_init(Condition_Composite *condition_composite, Selects *select_left, Expression *right, CompOp cp){
  condition_composite->left = nullptr;
  condition_composite->right = right;
  condition_composite->select_attr_left = (void*)select_left;
  condition_composite->select_attr_right = nullptr;
  condition_composite->comp = cp;
}
void condition_exp_select_init(Condition_Composite *condition_composite, Expression *left, Selects *select_right, CompOp cp){
  condition_composite->left = left;
  condition_composite->right = nullptr;
  condition_composite->select_attr_left = nullptr;
  condition_composite->select_attr_right = (void*)select_right;
  condition_composite->comp = cp;
}

void condition_init(Condition *condition, CompOp comp, 
                    int left_is_attr, RelAttr *left_attr, Value *left_value,
                    int right_is_attr, RelAttr *right_attr, Value *right_value) {
  condition->comp = comp;
  condition->left_is_attr = left_is_attr;
  if (left_is_attr) {
    condition->left_attr = *left_attr;
  } else {
    condition->left_value = *left_value;
  }

  condition->right_is_attr = right_is_attr;
  if (right_is_attr) {
    condition->right_attr = *right_attr;
  } else {
    condition->right_value = *right_value;
  }
}
void condition_destroy(Condition *condition) {
  if (condition->left_is_attr) {
    relation_attr_destroy(&condition->left_attr);
  } else {
    value_destroy(&condition->left_value);
  }
  if (condition->right_is_attr) {
    relation_attr_destroy(&condition->right_attr);
  } else {
    value_destroy(&condition->right_value);
  }
}
void complex_condition_destroy(Condition_Composite *condition){
  if (condition->left != nullptr) expression_destroy(condition->left);
  if (condition->right != nullptr) expression_destroy(condition->right);
  if (condition->select_attr_right != nullptr) {
    selects_destroy((Selects *)condition->select_attr_right);
  }
  condition->left = nullptr;
  condition->right = nullptr;
  condition->select_attr_right = nullptr;
  free(condition);
}
void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length) {
  attr_info->name = strdup(name);
  attr_info->type = type;
  attr_info->length = length;
}
void attr_info_destroy(AttrInfo *attr_info) {
  free(attr_info->name);
  attr_info->name = nullptr;
}

void group_by_append_relattr(GroupBy *g,const char *relName,const char *attrName){
  if (relName != NULL){
    g->attributes[g->attr_num].relation_name = strdup(relName);
  }else{
    g->attributes[g->attr_num].relation_name = nullptr;
  }
  g->attributes[g->attr_num++].attribute_name = strdup(attrName);
}

void order_by_append_relattr(OrderBy *o,const char *relName,const char *attrName,const int order){
  o->up_or_down[o->attr_num] = order;
  if (relName != NULL){
    o->attributes[o->attr_num].relation_name = strdup(relName);
  }else{
     o->attributes[o->attr_num].relation_name = nullptr;
  }
  o->attributes[o->attr_num++].attribute_name = strdup(attrName);
}

void cal(Expression *expression){
  if (expression == nullptr){
    return ;
  }
  if (expression->is_leaf) {
    if (expression->is_attr) {
      if (expression->attr.relation_name != nullptr){
      LOG_INFO("rel %s",expression->attr.relation_name);
      }
      if (expression->attr.attribute_name){
      LOG_INFO("attr %s",expression->attr.attribute_name);
      }
      
    }
    else LOG_INFO(" %d ", *(int*)expression->value.data);
    return ;
  }
  //LOG_INFO("calleft");
  if (expression->left != nullptr) cal(expression->left);
  
  if (expression->right != nullptr) cal(expression->right);
  return ;
}
void show_expression(Expression *expression){
  if(expression != nullptr)cal(expression);
}

void show_order(RelAttr relattr, int up_or_down){
  if (relattr.relation_name != nullptr) LOG_INFO("order_rel %s",relattr.relation_name);
  LOG_INFO("order_attr %s   %d",relattr.attribute_name,up_or_down);
}
void show_group(RelAttr relattr){
  if (relattr.relation_name != nullptr) LOG_INFO("group_rel %s",relattr.relation_name);
  LOG_INFO("group_attr %s",relattr.attribute_name);
}
void show_join(JoinOn joinon){
  LOG_INFO("%s", joinon.relation_name);
  LOG_INFO("show join on condition");
  for (size_t i = 0;i < joinon.condition_num;i++){
    show_condition(joinon.conditions[i]);
  }
}
void show_selects(Selects selects){
    LOG_INFO("show select_exp");
  for (size_t i = 0;i < selects.expression_select_num;i++){
    LOG_INFO("show %d", selects.expression_select_num);
    show_expression(selects.expression_select[i]);
  }
  
  LOG_INFO("show tables");
  for (size_t i = 0;i < selects.relation_num;i++){
    LOG_INFO("%s",selects.relations[i]);
  } 
  
  LOG_INFO("show join");
  for (size_t i = 0;i <= selects.join_num;i++){
    LOG_INFO("%d",selects.join_num);
    show_join(selects.join_on[i]);
  } 

  LOG_INFO("show condition");
  for (size_t i = 0;i < selects.condition_num;i++){
    LOG_INFO("show %d", selects.condition_num);
    show_condition(selects.conditions[i]);
  }

  LOG_INFO("show group");
  for (size_t i = 0;i < selects.group_by.attr_num;i++){
    LOG_INFO("show %d", selects.group_by.attr_num);
    show_group(selects.group_by.attributes[i]);
  }

  LOG_INFO("show order");
  for (size_t i = 0;i < selects.order_by.attr_num;i++){
    LOG_INFO("show %d", selects.order_by.attr_num);
    show_order(selects.order_by.attributes[i],selects.order_by.up_or_down[i]);
  }
}

Expression *select_expression_copy(Expression *expression){
  
  Expression *expression_select = (Expression *)malloc(sizeof(Expression));

  expression_select->is_leaf = expression->is_leaf;
  expression_select->is_attr = expression->is_attr;

  if (!expression->is_leaf) {
    expression_select->calculate = expression->calculate;
    if (expression->left != nullptr) {
      expression_select->left = select_expression_copy(expression->left);
    }else{
      expression_select->left = nullptr;
    }
    if (expression->right != nullptr) {
      expression_select->right = select_expression_copy(expression->right);  
    }else{
      expression_select->right = nullptr;
    }
  }else{
    if (expression->is_attr) {
        expression_select->attr = expression->attr;
      //LOG_INFO("%s",expression_select->attr.attribute_name);
    }else{
      expression_select->value = expression->value;
      //LOG_INFO(" %d %d", expression->value->type, expression_select->value->type);
    }
  }
  return expression_select;
}
Condition_Composite *select_condition_copy(Condition_Composite *condition){
  Condition_Composite *condition_select = (Condition_Composite *)malloc(sizeof(Condition_Composite));
  condition_select->comp = condition->comp;
  if (condition->left != nullptr) condition_select->left = select_expression_copy(condition->left);
  else condition_select->left = nullptr;
  if (condition->right != nullptr) condition_select->right = select_expression_copy(condition->right);
  else condition_select->right = nullptr;
  if (condition->select_attr_left != nullptr) condition_select->select_attr_left = condition->select_attr_left;
  else condition_select->select_attr_left = nullptr;
  if (condition->select_attr_right != nullptr) condition_select->select_attr_right = condition->select_attr_right;
  else condition_select->select_attr_right = nullptr;
  return condition_select;
}
// void selects_init(Selects *selects, ...);
void selects_append_attribute(Selects *selects, Expression *expression) {
  //LOG_INFO("%d",selects->expression_select_num);
  selects->expression_select[selects->expression_select_num++] = select_expression_copy(expression);
  // LOG_INFO("hhhhh %s%s%s ",rel_attr->relation_name,rel_attr->extra_attribute_name,rel_attr->attribute_name);
}
void selects_append_relation(Selects *selects, const char *relation_name) {
  selects->relations[selects->relation_num++] = strdup(relation_name);
}

void select_append_condition(Selects *selects, Condition_Composite *condition){
  selects->conditions[selects->condition_num++] = select_condition_copy(condition);
}

void select_join_append_condition(Selects *select, Condition_Composite *condition){
  JoinOn *joinon = &select->join_on[select->join_tmp];
  joinon->conditions[joinon->condition_num++] = select_condition_copy(condition);
}
void select_join_append_relation(Selects *select, const char *relation_name){
  select->join_num_max++;
  select->join_on[select->join_tmp].relation_name = strdup(relation_name);
  //LOG_INFO("%d  %s",select->join_tmp, select->join_on[select->join_tmp].relation_name);
}
void select_join_num_change(Selects *select,int num){
  if (num == 0) {
    select->join_tmp--;
  }
  else {
    select->join_num++;
    select->join_tmp = select->join_num;
  }
}

// void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num) {
//   // assert(condition_num <= sizeof(selects->conditions)/sizeof(selects->conditions[0]));
//   // for (size_t i = 0; i < condition_num; i++) {
//   //   selects->conditions[i] = conditions[i];
//   // }
//   // selects->condition_num = condition_num;
// }
void expression_destroy(Expression *expression){
  expression->calculate = CAL_IDEO;
  if (expression->is_leaf){
    if (expression->is_attr){
      relation_attr_destroy(&expression->attr);
    }else{
      value_destroy(&expression->value);
    }
  }else{
    if (expression->left != nullptr) expression_destroy(expression->left);
    if (expression->right != nullptr) expression_destroy(expression->right);
  }
  expression->left = nullptr;
  expression->right = nullptr;
  expression->is_leaf = 0;
  expression->is_attr = 0;
  free(expression);
}

void join_destroy(JoinOn *joinon){
  free(joinon->relation_name);
  joinon->relation_name = nullptr;
  for (size_t i = 0;i < joinon->condition_num;i++){
    complex_condition_destroy(joinon->conditions[i]);
  }
}

void group_destroy(GroupBy *groupby){
  for (size_t i = 0;i < groupby->attr_num ;i++){
    relation_attr_destroy(&groupby->attributes[i]);
  }
  groupby->attr_num = 0;
}

void order_destroy(OrderBy *orderby){
  for (size_t i = 0;i < orderby->attr_num ;i++){
    relation_attr_destroy(&orderby->attributes[i]);
  }
  orderby->attr_num = 0;
}

void selects_destroy(Selects *selects) {
  LOG_INFO("doing destroy");
  for (size_t i = 0; i < selects->expression_select_num; i++) {
    LOG_INFO("doing destroy");
    expression_destroy(selects->expression_select[i]);
  }
  selects->expression_select_num = 0;

  for (size_t i = 0; i < selects->relation_num; i++) {
    free(selects->relations[i]);
    selects->relations[i] = NULL;
  }
  selects->relation_num = 0;

  for (size_t i = 0; i < selects->join_num_max; i++)
  {
    join_destroy(&selects->join_on[i]);
  }
  selects->join_num_max = 0;
  selects->join_tmp = 0;
  selects->join_num = 0;

  for (size_t i = 0; i < selects->condition_num; i++) {
    complex_condition_destroy(selects->conditions[i]);
  }  
  group_destroy(&selects->group_by);
  order_destroy(&selects->order_by);
  // selects->condition_num = 0;

}

void inserts_record_init(Inserts *inserts, const char *relation_name, Value values[][MAX_NUM], size_t record_num, size_t value_nums[]) {
  //assert(value_num <= sizeof(inserts->values)/sizeof(inserts->values[0])); //unknow assert
  
  inserts->relation_name = strdup(relation_name);
  for (size_t i = 0; i < record_num; i++) {
      for(size_t j = 0; j < value_nums[i]; j++){
        inserts->record_values[i][j] = values[i][j];
      }
      inserts->values_num[i] = value_nums[i];
  }
  inserts->record_num = record_num;
  
}

void inserts_init(Inserts *inserts, const char *relation_name, Value values[], size_t value_num) {
  assert(value_num <= sizeof(inserts->values)/sizeof(inserts->values[0]));
  
  inserts->relation_name = strdup(relation_name);
  for (size_t i = 0; i < value_num; i++) {
    inserts->values[i] = values[i];
  }
  inserts->value_num = value_num;
  
}

void inserts_destroy(Inserts *inserts) {
  free(inserts->relation_name);
  inserts->relation_name = nullptr;
  
  for (size_t i = 0; i < inserts->record_num; i++) {
    for (size_t j = 0; j < inserts->values_num[i]; j++){
      value_destroy(&inserts->record_values[i][j]);
    }
    inserts->values_num[i] = 0;
  }
  inserts->value_num = 0;
  inserts->record_num = 0;
}

void deletes_init_relation(Deletes *deletes, const char *relation_name) {
  deletes->relation_name = strdup(relation_name);
}

void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num) {
  assert(condition_num <= sizeof(deletes->conditions)/sizeof(deletes->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    deletes->conditions[i] = conditions[i];
  }
  deletes->condition_num = condition_num;
}
void deletes_destroy(Deletes *deletes) {
  for (size_t i = 0; i < deletes->condition_num; i++) {
    condition_destroy(&deletes->conditions[i]);
  }
  deletes->condition_num = 0;
  free(deletes->relation_name);
  deletes->relation_name = nullptr;
}

void updates_init(Updates *updates, const char *relation_name, const char *attribute_name,
                  Value *value, Condition conditions[], size_t condition_num) {
  updates->relation_name = strdup(relation_name);
  updates->attribute_name = strdup(attribute_name);
  updates->value = *value;

  assert(condition_num <= sizeof(updates->conditions)/sizeof(updates->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    updates->conditions[i] = conditions[i];
  }
  updates->condition_num = condition_num;
}

void updates_destroy(Updates *updates) {
  free(updates->relation_name);
  free(updates->attribute_name);
  updates->relation_name = nullptr;
  updates->attribute_name = nullptr;

  value_destroy(&updates->value);

  for (size_t i = 0; i < updates->condition_num; i++) {
    condition_destroy(&updates->conditions[i]);
  }
  updates->condition_num = 0;
}

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info) {
  create_table->attributes[create_table->attribute_count++] = *attr_info;
}
void create_table_init_name(CreateTable *create_table, const char *relation_name) {
  create_table->relation_name = strdup(relation_name);
}
void create_table_destroy(CreateTable *create_table) {
  for (size_t i = 0; i < create_table->attribute_count; i++) {
    attr_info_destroy(&create_table->attributes[i]);
  }
  create_table->attribute_count = 0;
  free(create_table->relation_name);
  create_table->relation_name = nullptr;
}

void drop_table_init(DropTable *drop_table, const char *relation_name) {
  drop_table->relation_name = strdup(relation_name);
}
void drop_table_destroy(DropTable *drop_table) {
  free(drop_table->relation_name);
  drop_table->relation_name = nullptr;
}

void create_index_init(CreateIndex *create_index, const char *index_name, 
                       const char *relation_name, const char *attr_name) {
  create_index->index_name = strdup(index_name);
  create_index->relation_name = strdup(relation_name);
  create_index->attribute_name = strdup(attr_name);
}
void create_index_destroy(CreateIndex *create_index) {
  free(create_index->index_name);
  free(create_index->relation_name);
  free(create_index->attribute_name);

  create_index->index_name = nullptr;
  create_index->relation_name = nullptr;
  create_index->attribute_name = nullptr;
}

void drop_index_init(DropIndex *drop_index, const char *index_name) {
  drop_index->index_name = strdup(index_name);
}
void drop_index_destroy(DropIndex *drop_index) {
  free((char *)drop_index->index_name);
  drop_index->index_name = nullptr;
}

void desc_table_init(DescTable *desc_table, const char *relation_name) {
  desc_table->relation_name = strdup(relation_name);
}

void desc_table_destroy(DescTable *desc_table) {
  free((char *)desc_table->relation_name);
  desc_table->relation_name = nullptr;
}

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name) {
  load_data->relation_name = strdup(relation_name);

  if (file_name[0] == '\'' || file_name[0] == '\"') {
    file_name++;
  }
  char *dup_file_name = strdup(file_name);
  int len = strlen(dup_file_name);
  if (dup_file_name[len - 1] == '\'' || dup_file_name[len - 1] == '\"') {
    dup_file_name[len - 1] = 0;
  }
  load_data->file_name = dup_file_name;
}

void load_data_destroy(LoadData *load_data) {
  free((char *)load_data->relation_name);
  free((char *)load_data->file_name);
  load_data->relation_name = nullptr;
  load_data->file_name = nullptr;
}

void query_init(Query *query) {
  query->flag = SCF_ERROR;
  memset(&query->sstr, 0, sizeof(query->sstr));
}

Query *query_create() {
  Query *query = (Query *)malloc(sizeof(Query));
  if (nullptr == query) {
    LOG_ERROR("Failed to alloc memroy for query. size=%ld", sizeof(Query));
    return nullptr;
  }

  query_init(query);
  return query;
}

void query_reset(Query *query) {
  switch (query->flag) {
    case SCF_SELECT: {
      selects_destroy(&query->sstr.selection[0]);
    }
    break;
    case SCF_INSERT: {
      inserts_destroy(&query->sstr.insertion);
    }
    break;
    case SCF_DELETE: {
      deletes_destroy(&query->sstr.deletion);
    }
    break;
    case SCF_UPDATE: {
      updates_destroy(&query->sstr.update);
    }
    break;
    case SCF_CREATE_TABLE: {
      create_table_destroy(&query->sstr.create_table);
    }
    break;
    case SCF_DROP_TABLE: {
      drop_table_destroy(&query->sstr.drop_table);
    }
    break;
    case SCF_CREATE_INDEX: {
      create_index_destroy(&query->sstr.create_index);
    }
    break;
    case SCF_DROP_INDEX: {
      drop_index_destroy(&query->sstr.drop_index);
    }
    break;
    case SCF_SYNC: {

    }
    break;
    case SCF_SHOW_TABLES:
    break;

    case SCF_DESC_TABLE: {
      desc_table_destroy(&query->sstr.desc_table);
    }
    break;

    case SCF_LOAD_DATA: {
      load_data_destroy(&query->sstr.load_data);
    }
    break;
    case SCF_BEGIN:
    case SCF_COMMIT:
    case SCF_ROLLBACK:
    case SCF_HELP:
    case SCF_EXIT:
    case SCF_ERROR:
    break;
  }
}

void query_destroy(Query *query) {
  query_reset(query);
  free(query);
}
#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

////////////////////////////////////////////////////////////////////////////////

extern "C" int sql_parse(const char *st, Query  *sqls);

RC parse(const char *st, Query *sqln) {
  sql_parse(st, sqln);
  //LOG_ERROR("par, %d",sqln->flag);
  if (sqln->flag == SCF_ERROR)
    return SQL_SYNTAX;
  else
    return SUCCESS;
}