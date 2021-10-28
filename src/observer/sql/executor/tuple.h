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
// Created by Wangyunlai on 2021/5/14.
//

#ifndef __OBSERVER_SQL_EXECUTOR_TUPLE_H_
#define __OBSERVER_SQL_EXECUTOR_TUPLE_H_

#include <memory>
#include <vector>
#include <string>

#include "common/log/log.h"
#include "sql/parser/parse.h"
#include "sql/executor/value.h"

class Table;

class Tuple {
public:
  Tuple() = default;

  Tuple(const Tuple &other);

  ~Tuple();

  Tuple(Tuple &&other) noexcept ;
  Tuple & operator=(Tuple &&other) noexcept ;

  void add(TupleValue *value);
  void add(const std::shared_ptr<TupleValue> &other);
  void add(int value);
  void add(float value);
  void add(const char *s, int len);
  void add(const char *s, int len, bool is_date);
  
  const std::vector<std::shared_ptr<TupleValue>> &values() const {
    return values_;
  }

  int size() const {
    return values_.size();
  }

  const TupleValue &get(int index) const {
    return *values_[index];
  }

  const std::shared_ptr<TupleValue> &get_pointer(int index) const {
    return values_[index];
  }

private:
  std::vector<std::shared_ptr<TupleValue>>  values_;
};

class TupleField {
public:
  TupleField(AttrType type, const char *table_name, const char *field_name, const char *calcu_name) :
          type_(type), table_name_(table_name), field_name_(field_name), calcu_name_(calcu_name){
  }
  TupleField(AttrType type, const char *table_name, const char *field_name) :
          type_(type), table_name_(table_name), field_name_(field_name){
  }
  AttrType  type() const{
    return type_;
  }

  const char *table_name() const {
    return table_name_.c_str();
  }
  const char *field_name() const {
    return field_name_.c_str();
  }
  const char *calcu_name() const{
    return calcu_name_.c_str();
  }
  std::string to_string() const;
private:
  std::string calcu_name_;
  AttrType  type_;
  std::string table_name_;
  std::string field_name_;
};

class TupleSchema {
public:
  TupleSchema() = default;
  ~TupleSchema() = default;

  void add(AttrType type, const char *table_name, const char *field_name);
  void add(AttrType type, const char *table_name, const char *field_name, const char *calcu_name);
  void add_if_not_exists(AttrType type, const char *table_name, const char *field_name, const char *calcu_name);
  // void merge(const TupleSchema &other);
  void append(const TupleSchema &other);

  const std::vector<TupleField> &fields() const {
    return fields_;
  }

  const TupleField &field(int index) const {
    return fields_[index];
  }

  int index_of_field(const char *table_name, const char *field_name) const;
  void clear() {
    fields_.clear();
  }

  void print(std::ostream &os) const;
public:
  static void from_table(const Table *table, TupleSchema &schema);
private:
  std::vector<TupleField> fields_;
};

class TupleSet {
public:
  TupleSet() = default;
  TupleSet(TupleSet &&other);
  explicit TupleSet(const TupleSchema &schema) : schema_(schema) {
  }
  TupleSet &operator =(TupleSet &&other);

  ~TupleSet() = default;

  void set_schema(const TupleSchema &schema);

  const TupleSchema &get_schema() const;

  void add(Tuple && tuple);

  void clear();
  void check_calculate(){
    size_t fields_size = schema_.fields().size();
    Tuple tuple_out;
    TupleSchema schema_out;
    //LOG_INFO("sum is %d",(int)fields_size);
    for (size_t i = 0; i < fields_size; i++)
    {
      
      //若是没有计算要求
      const char *calcu_name = schema_.field(i).calcu_name();
      if (0 == strcmp("IDEO",calcu_name))
      {
        return ;
      }
      std::string str = schema_.field(i).calcu_name();
      str.append("(").append(schema_.field(i).field_name()).append(")");
      schema_out.add_if_not_exists(schema_.field(i).type(),schema_.field(i).table_name(),str.c_str(),schema_.field(i).calcu_name());
      //计算COUNT
      if(0 == strcmp("COUNT",calcu_name))
      {
        
        size_t tuple_size = tuples_.size();
        int sum = 0;
        for (size_t j = 0; j < tuple_size ; j++){
          sum++;
        }
        
        tuple_out.add(sum);
        continue;
      }
      
      //筛选出的tuple为空
      size_t tuple_size = tuples_.size();
      if (tuple_size == 0)
      {
        const char *s = "zero_size";
        tuple_out.add(s,strlen(s));
        continue;
      }
      //Tuple tmp = tuples_[0].get(0);

      const AttrType attrtype = schema_.field(i).type();
      if (attrtype == INTS)
      {
        if (0 == strcmp("MAX",calcu_name)){
          int maxx = INT32_MIN;
          LOG_INFO("for size_t %d",(int)tuples_.size());
          for (size_t j = 0; j < tuples_.size(); j++)
          {
            const IntValue *val = (const IntValue *)((&tuples_[j].get(i)));
            //LOG_INFO("%d", val->get_value());
            if (val->get_value() > maxx){
              maxx = val->get_value();
              
            }
          }
          tuple_out.add(maxx);

        }else if (0 == strcmp("MIN",calcu_name)){
          int minn = INT32_MAX;
          LOG_INFO("for size_t %d",(int)tuples_.size());
          for (size_t j = 0; j < tuples_.size(); j++)
          {
            const IntValue *val = (const IntValue *)((&tuples_[j].get(i)));
            //LOG_INFO("%d", val->get_value());
            if (val->get_value() < minn){
              minn = val->get_value();
              
            }
          }
          tuple_out.add(minn);
        }else if (0 == strcmp("AVG",calcu_name)){
          int sum = 0;
          int nums = 0;
          LOG_INFO("for size_t %d",(int)tuples_.size());
          for (size_t j = 0; j < tuples_.size(); j++)
          {
            const IntValue *val = (const IntValue *)((&tuples_[j].get(i)));
            sum += val->get_value();
            nums += 1;
          }
          tuple_out.add((float)((float)sum / nums));
        }
      }
      else if (attrtype == FLOATS)
      {
        if (0 == strcmp("MAX",calcu_name)){
          const FloatValue *val = (const FloatValue *)((&tuples_[0].get(i)));
          float maxx = val->get_value();
          LOG_INFO("for size_t %d",(int)tuples_.size());
          for (size_t j = 0; j < tuples_.size(); j++)
          {
            const FloatValue *val = (const FloatValue *)((&tuples_[j].get(i)));
            //LOG_INFO("%d", val->get_value());
            if (val->get_value() > maxx){
              maxx = val->get_value();
              
            }
          }
          tuple_out.add(maxx);

        }else if (0 == strcmp("MIN",calcu_name)){
          const FloatValue *val = (const FloatValue *)((&tuples_[0].get(i)));
          float minn = val->get_value();
          LOG_INFO("for size_t %d",(int)tuples_.size());
          for (size_t j = 0; j < tuples_.size(); j++)
          {
            const FloatValue *val = (const FloatValue *)((&tuples_[j].get(i)));
            //LOG_INFO("%d", val->get_value());
            if (val->get_value() < minn){
              minn = val->get_value();
              
            }
          }
          tuple_out.add(minn);
        }else if (0 == strcmp("AVG",calcu_name)){
          float sum = 0;
          int nums = 0;
          LOG_INFO("for size_t %d",(int)tuples_.size());
          for (size_t j = 0; j < tuples_.size(); j++)
          {
            const FloatValue *val = (const FloatValue *)((&tuples_[j].get(i)));
            sum += val->get_value();
            nums += 1;
          }
          tuple_out.add((float)((float)sum / nums));
        }
      }
    }

    schema_.clear();
    schema_.append(schema_out);
    tuples_.clear();
    tuples_.emplace_back(std::move(tuple_out));
    
  };
  bool is_empty() const;
  int size() const;
  const Tuple &get(int index) const;
  const std::vector<Tuple> &tuples() const;

  void print(std::ostream &os) const;
public:
  const TupleSchema &schema() const {
    return schema_;
  }
private:
  std::vector<Tuple> tuples_;
  TupleSchema schema_;
};

class TupleRecordConverter {
public:
  TupleRecordConverter(Table *table, TupleSet &tuple_set);

  void add_record(const char *record);
private:
  Table *table_;
  TupleSet &tuple_set_;
};

#endif //__OBSERVER_SQL_EXECUTOR_TUPLE_H_
