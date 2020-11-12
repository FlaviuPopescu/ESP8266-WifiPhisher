#ifndef Credential_h
#define Credential_h

#include "Arduino.h"
#include "ArduinoJson.h"
#include "SimpleList.h"
#include "language.h"

extern bool readFile(String path, String &buf);
extern bool appendFile(String path, String &buf);
extern bool writeFile(String path, String &buf);

struct SocialAccount {
  String user;
  String pass;
};

class Credential {
public:
  Credential();
  ~Credential();

  void init();
  String get();
  int count(String key);
  void save(String key, String name, String number);
  void deleteIndex(String key, int id);
  void deleteAll();
  String getSocialUser(String key, int id);
  String getSocialPass(String key, int id);
  void setNameWifi(String name);

  void toSerial();

private:
  String FILE_PATH = "/credential.json";
  String FILE_WIFI_PATH = "/wifissid.json";
  String buf;
  bool isExist(JsonObject &root, String key);
  void add(String key, String user, String pass);
  
  SimpleList<SocialAccount> *listFacebook;
  SimpleList<SocialAccount> *listWifi;

};

#endif
