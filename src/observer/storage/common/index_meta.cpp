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
// Created by wangyunlai.wyl on 2021/5/18.
//
#include <vector>
#include "storage/common/index_meta.h"
#include "storage/common/field_meta.h"
#include "storage/common/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "rc.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");
const static Json::StaticString FIELD_FIELD_NAME_VECTOR("field_name_vector");
const static Json::StaticString FIELD_UNIQUE("field_unique");

RC IndexMeta::init(const char *name, const FieldMeta &field)
{
  if (nullptr == name || common::is_blank(name))
  {
    return RC::INVALID_ARGUMENT;
  }
  field_num_ = 1;
  name_ = name;
  field_ = field.name();
  return RC::SUCCESS;
}

RC IndexMeta::init(const char *name, std::vector<FieldMeta> &field_vec, int is_unique)
{
  name_ = name;
  unique_ = is_unique;
  field_num_ = (int)field_vec.size();
  
  if (nullptr == name || common::is_blank(name))
  {
    return RC::INVALID_ARGUMENT;
  }
  
  for (auto fie : field_vec)
  {
    field_vec_.push_back(fie.name());
  }

  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME] = name_;
  json_value[FIELD_FIELD_NAME] = field_;
  json_value[FIELD_UNIQUE] = unique_;
  Json::Value field_values;
  for (auto &it : field_vec_)
  {
    Json::Value field_value;
    field_value[FIELD_FIELD_NAME] = it;
    field_values.append(std::move(field_value));
  }
  json_value[FIELD_FIELD_NAME_VECTOR] = std::move(field_values);
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &field_value = json_value[FIELD_FIELD_NAME];
  const Json::Value &field_vec_value = json_value[FIELD_FIELD_NAME_VECTOR];
  const Json::Value &unique = json_value[FIELD_UNIQUE];
  if (!name_value.isString())
  {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  if (field_vec_value.empty() || !field_vec_value.isArray())
  {
    LOG_ERROR("Invalid field_vec_value, json value=%s", field_vec_value.toStyledString().c_str());
    return RC::SCHEMA_FIELD_MISSING;
  }
  const int field_num = field_vec_value.size();
  LOG_INFO("field_vec_value.size() %d",(int)field_vec_value.size());
  std::vector<FieldMeta> field_vec(field_num);
  for (int i = 0; i < field_num; i++)
  {
    
    const FieldMeta *field = table.field(field_vec_value[i][FIELD_FIELD_NAME].asCString());
    if (nullptr == field)
    {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_vec_value[i].asCString());
      return RC::SCHEMA_FIELD_MISSING;
    }
    field_vec[i] = *field;
  }

  return index.init(name_value.asCString(), field_vec, unique.asInt());
}

const char *IndexMeta::name() const
{
  return name_.c_str();
}

const char *IndexMeta::field() const
{
  return field_.c_str();
}

const std::vector<std::string> IndexMeta::field_vec() const
{
  return field_vec_;
}
const int IndexMeta::is_unique() const{
  return unique_;
}
void IndexMeta::desc(std::ostream &os) const
{
  os << "index name=" << name_
     << ", field=" << field_;
}