/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.x                          */
/*             Copyright (C)1998-2016, WWIV Software Services             */
/*                                                                        */
/*    Licensed  under the  Apache License, Version  2.0 (the "License");  */
/*    you may not use this  file  except in compliance with the License.  */
/*    You may obtain a copy of the License at                             */
/*                                                                        */
/*                http://www.apache.org/licenses/LICENSE-2.0              */
/*                                                                        */
/*    Unless  required  by  applicable  law  or agreed to  in  writing,   */
/*    software  distributed  under  the  License  is  distributed on an   */
/*    "AS IS"  BASIS, WITHOUT  WARRANTIES  OR  CONDITIONS OF ANY  KIND,   */
/*    either  express  or implied.  See  the  License for  the specific   */
/*    language governing permissions and limitations under the License.   */
/*                                                                        */
/**************************************************************************/
#ifndef __INCLUDED_INIFILE_H__
#define __INCLUDED_INIFILE_H__

#include <string>
#include <map>
#include <vector>

namespace wwiv {
namespace core {

std::string FilePath(const std::string& directoryName, const std::string& fileName);

class IniFile {
 public:
  IniFile(const std::string& filename, const std::string& primarySection);
  IniFile(const std::string& filename, const std::string& primarySection, const std::string& secondarySection);
  IniFile(const std::string& filename, const std::vector<std::string>& sections);
  // Constructor/Destructor
  virtual ~IniFile(); 

  // Member functions
  void Close();
  bool IsOpen() const { return open_; }

  template<typename T>
  const T value(const std::string& key, const T& default_value = T()) const {
    return static_cast<T>(GetNumericValueT(key, default_value));
  }
  template<>
  const std::string value(const std::string& key, const std::string& default_value) const {
    return GetStringValue(key, default_value);
  }
  template<>
  const bool value(const std::string& key, const bool& default_value) const {
    return GetBooleanValue(key, default_value);
  }

  const std::string value(const std::string& key) const {
    return value<std::string>(key, "");
  }

private:
  // This class should not be assigneable via '=' so remove the implicit operator=
  // and Copy constructor.
  IniFile(const IniFile& other) = delete;
  IniFile& operator=(const IniFile& other) = delete;
  const char* GetValue(const std::string& key, const char *default_value = nullptr) const;

  const std::string GetStringValue(const std::string& key, const std::string& default_value) const;
  const long GetNumericValueT(const std::string& key, long default_value = 0) const;
  const bool GetBooleanValue(const std::string& key, bool default_value = false) const;

  const std::string file_name_;
  bool open_;
  std::vector<std::string> sections_;
  std::map<std::string, std::string> data_;
};

}  // namespace core
}  // namespace wwiv

#endif  // __INCLUDED_INIFILE_H__
