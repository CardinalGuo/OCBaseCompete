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
// Created by wangyunlai.wyl on 2021/6/7.
//

#ifndef __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
#define __OBSERVER_SQL_PARSER_PARSE_DEFS_H__

#include <stddef.h>

#define MAX_INSERT_RECORD 10
#define MAX_NUM 20
#define MAX_REL_NAME 20
#define MAX_ATTR_NAME 20
#define MAX_ERROR_MESSAGE 20
#define MAX_DATA 50

//属性结构体
typedef struct {
  char *relation_name;   // relation name (may be NULL) 表名
  char *attribute_name;  // attribute name              属性名
  char *extra_attribute_name; //extra_attribute_name     额外属性名
} RelAttr;

typedef enum {
  EQUAL_TO,     //"="     0
  LESS_EQUAL,   //"<="    1
  NOT_EQUAL,    //"<>"    2
  LESS_THAN,    //"<"     3
  GREAT_EQUAL,  //">="    4
  GREAT_THAN,   //">"     5
  ATTR_IN,      // in       6
  ATTR_NOT_IN,  //  not in      7   
  NO_OP
} CompOp;

//属性值类型
typedef enum { UNDEFINED, CHARS, INTS, FLOATS ,DATES, NULL_TYPE} AttrType;

//属性值
typedef struct _Value {
  AttrType type;  // type of value
  void *data;     // value
} Value;

typedef struct _Condition {
  int left_is_attr;    // TRUE if left-hand side is an attribute
                       // 1时，操作符左边是属性名，0时，是属性值
  Value left_value;    // left-hand side value if left_is_attr = FALSE
  RelAttr left_attr;   // left-hand side attribute
  CompOp comp;         // comparison operator
  int right_is_attr;   // TRUE if right-hand side is an attribute
                       // 1时，操作符右边是属性名，0时，是属性值
  RelAttr right_attr;  // right-hand side attribute if right_is_attr = TRUE 右边的属性
  Value right_value;   // right-hand side value if right_is_attr = FALSE
} Condition;

typedef struct {
  size_t    attr_num;               // Length of attrs in Select clause
  RelAttr   attributes[10];    // attrs in Select clause
} GroupBy;

typedef struct {
  size_t    attr_num;               // Length of attrs in Select clause
  RelAttr   attributes[10];    // attrs in Select clause
  int    up_or_down[10];
} OrderBy;




// // struct of select
// typedef struct {
//   size_t    attr_num;               // Length of attrs in Select clause
//   RelAttr   attributes[MAX_NUM];    // attrs in Select clause
//   size_t    relation_num;           // Length of relations in Fro clause
//   char *    relations[MAX_NUM];     // relations in From clause
//   size_t    condition_num;          // Length of conditions in Where clause
//   Condition conditions[MAX_NUM];    // conditions in Where clause
// } Selects;

//SELECTEXP   ID, COUNT(ID), ID DOT ID, COUNT(ID DOT ID), (RES) +-*/ (RES)

typedef enum {NONEOPERATOR, CAL_ADD, CAL_SUB, CAL_MUL, CAL_DIV, CAL_COUNT, CAL_MAX, CAL_MIN, CAL_AVG, CAL_MINUS, CAL_SELF, CAL_IDEO} Calculate;

typedef struct _Expression{
  Calculate calculate;
  int is_attr; //1 时是属性
  int is_leaf;  //
  Value value;
  RelAttr attr;
  struct _Expression *left; //if exist
  struct _Expression *right; //if exist
} Expression;




typedef struct _Condition_Composite {
  Expression *left;
  CompOp comp;         // comparison operator
  Expression *right;
  void *select_attr_right;
  void *select_attr_left;
} Condition_Composite;

typedef struct {
  char *    relation_name
  size_t    condition_num;          // Length of conditions in Where clause
  Condition_Composite *conditions[4];    // conditions in Where clause
} JoinOn;

typedef struct _Selects{
  size_t    relation_num;           // Length of relations in Fro clause
  char *    relations[10];     // relations in From clause
  
  size_t    expression_select_num;
  Expression *expression_select[30];
  
  size_t    condition_num;
  Condition_Composite *conditions[10];
  
  size_t join_num;
  size_t join_tmp;
  JoinOn join_on[10];
  size_t join_num_max;
  GroupBy group_by;
  OrderBy order_by;
} Selects;

// struct of insert
typedef struct {
  char *relation_name;    // Relation to insert into
  size_t value_num;       // Length of values
  size_t record_num;       // Length of records
  size_t values_num[MAX_INSERT_RECORD];
  Value record_values[MAX_INSERT_RECORD][MAX_NUM];
  Value values[MAX_NUM];  // values to insert
} Inserts;

// struct of delete
typedef struct {
  char *relation_name;            // Relation to delete from
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Deletes;

// struct of update
typedef struct {
  char *relation_name;            // Relation to update
  char *attribute_name;           // Attribute to update
  Value value;                    // update value
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Updates;

typedef struct {
  char *name;     // Attribute name
  AttrType type;  // Type of attribute
  size_t length;  // Length of attribute
} AttrInfo;

// struct of craete_table
typedef struct {
  char *relation_name;           // Relation name
  size_t attribute_count;        // Length of attribute
  AttrInfo attributes[MAX_NUM];  // attributes
} CreateTable;

// struct of drop_table
typedef struct {
  char *relation_name;  // Relation name
} DropTable;

// struct of create_index
typedef struct {
  char *index_name;      // Index name
  char *relation_name;   // Relation name
  char *attribute_name;  // Attribute name
} CreateIndex;

// struct of  drop_index
typedef struct {
  const char *index_name;  // Index name
} DropIndex;

typedef struct {
  const char *relation_name;
} DescTable;

typedef struct {
  const char *relation_name;
  const char *file_name;
} LoadData;

union Queries {
  
  Selects selection[10];
  Inserts insertion;
  Deletes deletion;
  Updates update;
  CreateTable create_table;
  DropTable drop_table;
  CreateIndex create_index;
  DropIndex drop_index;
  DescTable desc_table;
  LoadData load_data;
  char *errors;
};

// 修改yacc中相关数字编码为宏定义
enum SqlCommandFlag {
  SCF_ERROR = 0,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_DROP_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_BEGIN,
  SCF_COMMIT,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT
};
// struct of flag and sql_struct
typedef struct Query {
  enum SqlCommandFlag flag;
  union Queries sstr;
} Query;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

void relation_attr_init_extra(RelAttr *relation_attr, const char *relation_name, const char *attribute_name, const char *attribute_name_extra);
void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name);
void relation_attr_destroy(RelAttr *relation_attr);
void show_select_num(int num);
Expression* select_expression_copy(Expression *expression);
void expression_init_node(Expression *expression, Expression *expression_left, Expression *expression_right, Calculate cal_tmp);
void show_expression(Expression *expression);
void expression_init_leaf(Expression *expression, Value *value);
void expression_init_leaf_attr(Expression *expression, RelAttr *attr);
void show_condition(Condition_Composite *con);
void show_selects(Selects select);
void record_init_from_values(Value *record, Value *values, size_t length);
void value_init_integer(Value *value, int v);
void value_init_NULL(Value *value, const char *v);
void value_init_float(Value *value, float v);
void value_init_string(Value *value, const char *v);
void value_destroy(Value *value);
void condition_select_exe_init(Condition_Composite *condition_composite, Selects *select_left, Expression *right, CompOp cp);
void condition_select_select_init(Condition_Composite *condition_composite, Selects *select_left, Selects *select_right, CompOp cp);
void condition_exp_select_init(Condition_Composite *condition_composite, Expression *left, Selects *select_right, CompOp cp);
void condition_exp_exp_init(Condition_Composite *condition_composite, Expression *left, Expression *right, CompOp cp);

void condition_init(Condition *condition, CompOp comp, int left_is_attr, RelAttr *left_attr, Value *left_value,
    int right_is_attr, RelAttr *right_attr, Value *right_value);
void condition_destroy(Condition *condition);

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length);
void attr_info_destroy(AttrInfo *attr_info);


void group_by_append_relattr(GroupBy *g,const char *relName,const char *attrName);
void order_by_append_relattr(OrderBy *o,const char *relName,const char *attrName,const int order);
// void selects_init(Selects *selects, ...);
void selects_append_attribute(Selects *selects, Expression *expression);
void selects_append_relation(Selects *selects, const char *relation_name);
void select_append_condition(Selects *selects, Condition_Composite *condition);
// void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num);
// void selects_destroy(Selects *selects);
void select_join_append_condition(Selects *select, Condition_Composite *condition);
void select_join_append_relation(Selects *select, const char *attribute_name);
void select_join_num_change(Selects *select,int num);


void inserts_record_init(Inserts *inserts, const char *relation_name, Value values[][MAX_NUM], size_t record_num, size_t value_nums[]);
void inserts_init(Inserts *inserts, const char *relation_name, Value values[], size_t value_num);
void inserts_destroy(Inserts *inserts);

void complex_condition_destroy(Condition_Composite *condition);
void expression_destroy(Expression *expression);
void join_destroy(JoinOn *joinon);
void group_destroy(GroupBy *groupby);
void order_destroy(OrderBy *orderby);
void selects_destroy(Selects *selects);



void deletes_init_relation(Deletes *deletes, const char *relation_name);
void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num);
void deletes_destroy(Deletes *deletes);

void updates_init(Updates *updates, const char *relation_name, const char *attribute_name, Value *value,
    Condition conditions[], size_t condition_num);
void updates_destroy(Updates *updates);

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info);
void create_table_init_name(CreateTable *create_table, const char *relation_name);
void create_table_destroy(CreateTable *create_table);

void drop_table_init(DropTable *drop_table, const char *relation_name);
void drop_table_destroy(DropTable *drop_table);

void create_index_init(
    CreateIndex *create_index, const char *index_name, const char *relation_name, const char *attr_name);
void create_index_destroy(CreateIndex *create_index);

void drop_index_init(DropIndex *drop_index, const char *index_name);
void drop_index_destroy(DropIndex *drop_index);

void desc_table_init(DescTable *desc_table, const char *relation_name);
void desc_table_destroy(DescTable *desc_table);

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name);
void load_data_destroy(LoadData *load_data);

void query_init(Query *query);
Query *query_create();  // create and init
void query_reset(Query *query);
void query_destroy(Query *query);  // reset and delete

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // __OBSERVER_SQL_PARSER_PARSE_DEFS_H__