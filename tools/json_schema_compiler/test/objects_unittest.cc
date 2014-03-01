// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "tools/json_schema_compiler/test/objects.h"

#include "testing/gtest/include/gtest/gtest.h"

using namespace test::api::objects;

TEST(JsonSchemaCompilerObjectsTest, ObjectParamParamsCreate) {
  {
    scoped_ptr<ListValue> strings(new ListValue());
    strings->Append(Value::CreateStringValue("one"));
    strings->Append(Value::CreateStringValue("two"));
    scoped_ptr<DictionaryValue> info_value(new DictionaryValue());
    info_value->Set("strings", strings.release());
    info_value->Set("integer", Value::CreateIntegerValue(5));
    info_value->Set("boolean", Value::CreateBooleanValue(true));

    scoped_ptr<ListValue> params_value(new ListValue());
    params_value->Append(info_value.release());
    scoped_ptr<ObjectParam::Params> params(
        ObjectParam::Params::Create(*params_value));
    EXPECT_TRUE(params.get());
    EXPECT_EQ((size_t) 2, params->info.strings.size());
    EXPECT_EQ("one", params->info.strings[0]);
    EXPECT_EQ("two", params->info.strings[1]);
    EXPECT_EQ(5, params->info.integer);
    EXPECT_TRUE(params->info.boolean);
  }
  {
    scoped_ptr<ListValue> strings(new ListValue());
    strings->Append(Value::CreateStringValue("one"));
    strings->Append(Value::CreateStringValue("two"));
    scoped_ptr<DictionaryValue> info_value(new DictionaryValue());
    info_value->Set("strings", strings.release());
    info_value->Set("integer", Value::CreateIntegerValue(5));

    scoped_ptr<ListValue> params_value(new ListValue());
    params_value->Append(info_value.release());
    scoped_ptr<ObjectParam::Params> params(
        ObjectParam::Params::Create(*params_value));
    EXPECT_FALSE(params.get());
  }
}

TEST(JsonSchemaCompilerObjectsTest, ReturnsObjectResultCreate) {
  scoped_ptr<ReturnsObject::Result::Info> info(
      new ReturnsObject::Result::Info());
  info->state = ReturnsObject::Result::Info::STATE_FOO;
  scoped_ptr<Value> result_value(
      ReturnsObject::Result::Create(*info));
  DictionaryValue* result_dict = NULL;
  EXPECT_TRUE(result_value->GetAsDictionary(&result_dict));
  std::string state;
  EXPECT_TRUE(result_dict->GetString("state", &state));
  EXPECT_EQ("foo", state);
}
