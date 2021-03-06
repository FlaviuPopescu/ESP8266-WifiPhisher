#include "WifiConfigData.h"
#include "images.h"

WifiConfigData::WifiConfigData() { list = new SimpleList<WIFI>; }

void WifiConfigData::init() {
  buf = String();
  readFile(FILE_PATH, buf);
  DynamicJsonBuffer jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject(buf);

  if (isExist(root, F("wifi"))) {
    JsonArray &values = root[F("wifi")];
    int size = values.size();
    for (int id = 0; id < size; id++) {
      add(false, values[id][0], values[id][1]);
    }
  } else {
    deleteAll();
  }
  buf = String();
}

void WifiConfigData::initLCD() {
  display.init();
#ifndef FLIP_DIPLAY
  display.flipScreenVertically();
#endif // ifndef FLIP_DIPLAY
  display.clear();
  display.display();
}

WifiConfigData::~WifiConfigData() {}

void WifiConfigData::select(String ssid) {
  for (int i = 0; i < list->size(); i++) {
    if (getSSID(i).equalsIgnoreCase(ssid))
      select(i);
  }
}

void WifiConfigData::deselect(String ssid) {
  for (int i = 0; i < list->size(); i++) {
    if (getSSID(i).equalsIgnoreCase(ssid))
      deselect(i);
  }
}

bool WifiConfigData::getSelected(int num) {
  if (!check(num))
    return false;

  return list->get(num).selected;
}

String WifiConfigData::getSelectedStr(int num) { return b2a(getSelected(num)); }

void WifiConfigData::select(int num) {
  if (!check(num))
    return;

  for (int i = 0; i < list->size(); i++) {
    internal_deselect(i);
  }

  internal_select(num);
  prntln(getSSID(num));
}

void WifiConfigData::deselect(int num) {
  if (!check(num))
    return;

  internal_deselect(num);
  prntln(getSSID(num));
}

bool WifiConfigData::check(int num) {
  if (internal_check(num))
    return true;
  prntln((String)num);
  return false;
}

void WifiConfigData::add(bool selected, String ssid, String pass) {
  list->add(WIFI{selected, ssid.c_str(), pass.c_str()});
}

unsigned long timeout = 60000; // 1 minute


void WifiConfigData::disconnect() { WiFi.disconnect(); }

void WifiConfigData::setSSID(String ssid) { _ssid = ssid; }

void WifiConfigData::save(String ssid, String pass) {
  buf = String();
  readFile(FILE_PATH, buf);
  DynamicJsonBuffer jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject(buf);

  if (!isExist(root, F("wifi"))) {
    JsonArray &values = root.createNestedArray(F("wifi"));
    JsonArray &array = jsonBuffer.createArray();
    array.add(ssid);
    array.add(pass);
    values.add(array);
  } else {
    JsonArray &values = root[F("wifi")];
    JsonArray &array = jsonBuffer.createArray();
    array.add(ssid);
    array.add(pass);
    values.add(array);
  }

  String data;
  root.printTo(data);
  if (!writeFile(FILE_PATH, data)) {
    prntln(FILE_PATH);
  }
  buf = String();
  toSerial();
}
void WifiConfigData::deleteAll() {
  String data = "{\"wifi\":[]}";
  if (!writeFile(FILE_PATH, data)) {
    prntln(FILE_PATH);
  }
  toSerial();
}

String WifiConfigData::get() {
  readFile(FILE_PATH, buf);
  return buf;
}

bool WifiConfigData::isExist(JsonObject &root, String key) {
  return root.containsKey(key);
}

void WifiConfigData::toSerial() {
  readFile(FILE_PATH, buf);
  Serial.print(F("wifi: "));
  Serial.println(buf);
  buf = String();
}

int WifiConfigData::count() { return list->size(); }
String WifiConfigData::getSSID(int id) { return list->get(id).ssid; }

String WifiConfigData::getPassword(int id) { return list->get(id).pass; }

String WifiConfigData::getSSID() { return _ssid; }
String WifiConfigData::getPass() {

  for (int i = 0; i < list->size(); i++) {
    if (getSSID(i).equalsIgnoreCase(_ssid) &&
        !getSSID(i).equalsIgnoreCase(S_SSID_DEFAULT)) {
      return getPassword(i);
    }
  }

  return "";
}

bool WifiConfigData::internal_check(int num) {
  return num >= 0 && num < count();
}

void WifiConfigData::internal_select(int num) {
  list->replace(num, WIFI{true, list->get(num).ssid, list->get(num).pass});
}

void WifiConfigData::internal_deselect(int num) {
  list->replace(num, WIFI{false, list->get(num).ssid, list->get(num).pass});
}

void WifiConfigData::internal_remove(int num) { list->remove(num); }
