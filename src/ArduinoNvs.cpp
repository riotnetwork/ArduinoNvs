// ArduinoNvs.cpp

// Copyright (c) 2018 Sinai RnD
// Copyright (c) 2016-2017 TridentTD

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#include "ArduinoNvs.h"

ArduinoNvs::ArduinoNvs(){
}

bool ArduinoNvs::begin(){
  _err = nvs_flash_init();
  if (_err == ESP_ERR_NVS_NO_FREE_PAGES) {
    const esp_partition_t* nvs_partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, NULL);
    _err = (esp_partition_erase_range(nvs_partition, 0, nvs_partition->size));
  }
  _err = nvs_open("storage", NVS_READWRITE, &_nvs_handle);

  if(_err != ESP_OK) return false;
  return true;  
}

void ArduinoNvs::close(){
   nvs_close(_nvs_handle);
}

bool ArduinoNvs::eraseAll(){
  _err = nvs_erase_all(_nvs_handle);
  if(_err != ESP_OK) return false;
  return commit();
}

bool ArduinoNvs::erase(String key){
  _err =  nvs_erase_key(_nvs_handle, key.c_str());
  if(_err != ESP_OK) return false;
  return commit();
}

bool ArduinoNvs::commit(){
  _err = nvs_commit(_nvs_handle);
  if(_err != ESP_OK) return false;
  return true;
}




bool ArduinoNvs::setInt(String key, uint8_t value){
  _err = nvs_set_u8(_nvs_handle, (char*)key.c_str(), value);
  if(_err != ESP_OK) return false;
  return commit(); 
}

bool ArduinoNvs::setInt(String key, int16_t value){
  _err = nvs_set_i16(_nvs_handle, (char*)key.c_str(), value);
  if(_err != ESP_OK) return false;
  return commit();
}

bool ArduinoNvs::setInt(String key, uint16_t value){
  _err = nvs_set_u16(_nvs_handle, (char*)key.c_str(), value);
  if(_err != ESP_OK) return false;
  return commit(); 
}

bool ArduinoNvs::setInt(String key, int32_t value){
  _err = nvs_set_i32(_nvs_handle, (char*)key.c_str(), value);
  if(_err != ESP_OK) return false;
  return commit();
}

bool ArduinoNvs::setInt(String key, uint32_t value){
  _err = nvs_set_u32(_nvs_handle, (char*)key.c_str(), value);
  if(_err != ESP_OK) return false;
  return commit(); 
}
bool ArduinoNvs::setInt(String key, int64_t value){
  _err = nvs_set_i64(_nvs_handle, (char*)key.c_str(), value);
  if(_err != ESP_OK) return false;
  return commit();
}

bool ArduinoNvs::setInt(String key, uint64_t value){
  _err = nvs_set_u64(_nvs_handle, (char*)key.c_str(), value);
  if(_err != ESP_OK) return false;  
  return commit();
}

bool ArduinoNvs::setCharArray(String key, const char* value){
  _err = nvs_set_str(_nvs_handle, (char*)key.c_str(), value);
  if(_err != ESP_OK) return false;
  return commit(); 
}

bool ArduinoNvs::setString(String key, String value){
  _err = nvs_set_str(_nvs_handle, (char*)key.c_str(), (char*)value.c_str());
  if(_err != ESP_OK) return false;
  return commit(); 
}

bool ArduinoNvs::setObject(String key, void* value, size_t length){
  DEBUG_PRINTF("ArduinoNvs::setObjct(): set obj addr = [0x%X], length = [%d]\n", (int32_t)value, length);
  _err = nvs_set_blob(_nvs_handle, (char*)key.c_str(), value, length);
  if (_err) {
    DEBUG_PRINTF("ArduinoNvs::setObjct(): err = [0x%X]\n", _err);
    return false;
  }
  return commit();
}


int64_t ArduinoNvs::getInt(String key){
  uint8_t   v_u8;
  int16_t   v_i16;
  uint16_t  v_u16;
  int32_t   v_i32;
  uint32_t  v_u32;
  int64_t   v_i64;
  uint64_t  v_u64;

  _err = nvs_get_u8(_nvs_handle, (char*)key.c_str(), &v_u8);
  if(_err == ESP_OK) return (int64_t) v_u8;

  _err = nvs_get_i16(_nvs_handle, (char*)key.c_str(), &v_i16);
  if(_err == ESP_OK) return (int64_t) v_i16;

  _err = nvs_get_u16(_nvs_handle, (char*)key.c_str(), &v_u16);
  if(_err == ESP_OK) return (int64_t) v_u16;

  _err = nvs_get_i32(_nvs_handle, (char*)key.c_str(), &v_i32);
  if(_err == ESP_OK) return (int64_t) v_i32;

  _err = nvs_get_u32(_nvs_handle, (char*)key.c_str(), &v_u32);
  if(_err == ESP_OK) return (int64_t) v_u32;

  _err = nvs_get_i64(_nvs_handle, (char*)key.c_str(), &v_i64);
  if(_err == ESP_OK) return (int64_t) v_i64;

  _err = nvs_get_u64(_nvs_handle, (char*)key.c_str(), &v_u64);
  if(_err == ESP_OK) return (int64_t) v_u64;

  return 0;
}

bool ArduinoNvs::getString(String key, String& res){
  size_t required_size;
  esp_err_t err;
  
  err = nvs_get_str(_nvs_handle, key.c_str(), NULL, &required_size);
  if (err) return false;    
  
  char value[required_size];
  err = nvs_get_str(_nvs_handle, key.c_str(), value, &required_size);
  if (err) return false;
  res = value;
  return true;
}

String ArduinoNvs::getString(String key){
  String res;
  esp_err_t err = getString(key, res);
  if (err) return String();
  return res;
}

bool ArduinoNvs::getObject(String key, std::vector<uint8_t>& res){
  size_t required_size;
  esp_err_t err; 
  err = nvs_get_blob(_nvs_handle, key.c_str(), NULL, &required_size);
  if (err) {
    DEBUG_PRINTF("ArduinoNvs::getObject(): size err = [0x%X]\n", err);
    return false;
  }
  res.resize(required_size);  
  err = nvs_get_blob(_nvs_handle, key.c_str(), &res[0], &required_size);
  if (err) {
    DEBUG_PRINTF("ArduinoNvs::getObject(): get object err = [0x%X]\n", err);
    return false;
  }
  DEBUG_PRINTF("ArduinoNvs::getObject(): obj read, addr = [0x%X], size = [%d]\n", (int32_t)&res[0], res.size());
  return true;
}

std::vector<uint8_t> ArduinoNvs::getObject(String key){
  std::vector<uint8_t> res;
  esp_err_t err =  getObject(key, res);
  if (err) res.clear();
  return res;
}



bool ArduinoNvs::setFloat(String key, float value){
  return setObject(key, &value, sizeof(float));
}

float ArduinoNvs::getFloat(String key){
  std::vector<uint8_t> res(4);
  if (!getObject(key, res)) return 0;  
  return  *(float*)&res;
}

// bool ArduinoNvs::setDouble(String key, double value){
//   return setObject( key, &value, sizeof(double));
// }

// double ArduinoNvs::getDouble(String key){
//   double *pDouble = (double*) getObject(key);
//   return *pDouble;
// }

nvs_handle ArduinoNvs::get_nvs_handle(){
  return _nvs_handle;
}

ArduinoNvs NVS;
