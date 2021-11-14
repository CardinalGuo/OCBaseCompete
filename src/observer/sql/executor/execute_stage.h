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

#ifndef __OBSERVER_SQL_EXECUTE_STAGE_H__
#define __OBSERVER_SQL_EXECUTE_STAGE_H__

#include "common/seda/stage.h"
#include "sql/parser/parse.h"
#include "rc.h"
#include "storage/common/db.h"
#include "sql/executor/tuple.h"

class SessionEvent;

class ExecuteStage : public common::Stage {
public:
  ~ExecuteStage();
  static Stage *make_stage(const std::string &tag);

protected:
  // common function
  ExecuteStage(const char *tag);
  bool set_properties() override;
  RC check_select(const Selects selects, Db *datebase);
  RC check_table_valid(const Selects selects, Db *db);
  RC check_attri_valid(RelAttr attr, Selects selects, Db *db);
  RC check_aggrevage_valid(RelAttr attr, Selects selects, Db *db);
  RC check_condition_valid(Condition_Composite *condition, std::unordered_map<std::string, AttrType> &field_set, Db *datebase);
  RC check_join(std::unordered_map<std::string, AttrType> field_set,const JoinOn *joinon, Db *datebase);
  TupleSet combain_by_condition(int sets_size, std::vector<TupleSet> &tuplesets, const Selects selects);
  RC check_condition_value_equal(Condition condition,char *relations[MAX_NUM], size_t relation_num, Db *db);
  bool initialize() override;
  void cleanup() override;
  void handle_event(common::StageEvent *event) override;
  void callback_event(common::StageEvent *event,
                     common::CallbackContext *context) override;

  void handle_request(common::StageEvent *event);
  RC do_select(const char *db, Query *sql, SessionEvent *session_event);
protected:
private:
  Stage *default_storage_stage_ = nullptr;
  Stage *mem_storage_stage_ = nullptr;
};

#endif //__OBSERVER_SQL_EXECUTE_STAGE_H__
