#include "Stations.h"

Stations::Stations() { list = new SimpleList<Station>(); }

void Stations::add(uint8_t *mac, int accesspointNum) {
  int stationNum = findStation(mac);

  if (stationNum < 0) {
    internal_add(mac, accesspointNum);
    // print(list->size() - 1, list->size() == 1, false);
  } else {
    *getPkts(stationNum) += 1;
    *getTime(stationNum) = currentTime;
  }
  changed = true;
}

int Stations::findStation(uint8_t *mac) {
  int c = count();

  for (int i = 0; i < c; i++) {
    if (memcmp(getMac(i), mac, 6) == 0)
      return i;
  }
  return -1;
}

void Stations::sort() {
  list->setCompare([](Station &a, Station &b) -> int {
    if (*(a.pkts) > *(b.pkts))
      return -1;

    if (*(a.pkts) == *(b.pkts))
      return 0;

    return 1;
  });
  list->sort();
}

void Stations::sortAfterChannel() {
  list->setCompare([](Station &a, Station &b) -> int {
    if (a.ch < b.ch)
      return -1;

    if (a.ch == b.ch)
      return 0;

    return 1;
  });
  list->sort();
}

void Stations::removeAll() {
  internal_removeAll();
  changed = true;
}

void Stations::removeOldest() {
  int oldest = 0;
  int c = count();

  for (int i = 1; i < c; i++) {
    if (*getTime(i) > *getTime(oldest))
      oldest = i;
  }
  internal_remove(oldest);
  changed = true;
}

void Stations::printAll() {
  int c = count();

  if (c != 0)
    for (int i = 0; i < c; i++)
      print(i, i == 0, i == c - 1);
}

void Stations::printSelected() {
  int max = selected();
  int c = count();

  if (max == 0) {
    return;
  }

  for (int i = 0, j = 0; i < c && j < max; i++) {
    if (getSelected(i)) {
      print(i, j == 0, j == max - 1);
      j++;
    }
  }
}

void Stations::print(int num) { print(num, true, true); }

void Stations::print(int num, bool header, bool footer) {
  if (!check(num))
    return;

  if (header);

  prnt(leftRight(String(), (String)num, 2));
  prnt(leftRight(String(SPACE) + getMacStr(num), String(), 18));
  prnt(leftRight(String(SPACE), (String)getCh(num), 3));
  prnt(leftRight(String(SPACE) + getNameStr(num), String(), 17));
  prnt(leftRight(String(SPACE) + getVendorStr(num), String(), 9));
  prnt(leftRight(String(SPACE), (String)*getPkts(num), 9));
  prnt(leftRight(String(SPACE) + getAPStr(num), String(), 33));
  prnt(leftRight(String(SPACE) + getTimeStr(num), String(), 10));
  prntln(leftRight(String(SPACE) + getSelectedStr(num), String(), 9));

  if (footer);
}

String Stations::getAPStr(int num) {
  if (getAP(num) < 0)
    return String();

  return accesspoints.getSSID(getAP(num));
}

uint8_t *Stations::getAPMac(int num) {
  if (!check(num))
    return 0;

  return WiFi.BSSID(list->get(num).ap);
}

String Stations::getAPMacStr(int num) {
  if (!check(num))
    return String();

  uint8_t *mac = getAPMac(num);
  return bytesToStr(mac, 6);
}

int Stations::getAP(int num) {
  if (!check(num))
    return -1;

  return accesspoints.find(list->get(num).ap);
}

String Stations::getNameStr(int num) {
  if (!check(num))
    return String();

  return names.find(getMac(num));
}

bool Stations::hasName(int num) {
  if (!check(num))
    return false;

  return names.findID(getMac(num)) >= 0;
}

uint8_t *Stations::getMac(int num) {
  if (!check(num))
    return 0;

  return list->get(num).mac;
}

String Stations::getMacStr(int num) {
  if (!check(num))
    return String();

  uint8_t *mac = getMac(num);
  return bytesToStr(mac, 6);
}

String Stations::getMacVendorStr(int num) {
  String value;

  if (check(num)) {
    value = getVendorStr(num) + ":";
    uint8_t *mac = getMac(num);

    for (int i = 3; i < 6; i++) {
      if (mac[i] < 0x10)
        value += "0";
      value += String(mac[i], HEX);

      if (i < 5)
        value += ":";
    }
  }
  return value;
}

String Stations::getVendorStr(int num) {
  if (!check(num))
    return String();

  return searchVendor(list->get(num).mac);
}

String Stations::getSelectedStr(int num) { return b2a(getSelected(num)); }

uint32_t *Stations::getPkts(int num) {
  if (!check(num))
    return NULL;

  return list->get(num).pkts;
}

uint32_t *Stations::getTime(int num) {
  if (!check(num))
    return NULL;

  return list->get(num).time;
}

String Stations::getTimeStr(int num) {
  if (!check(num))
    return String();

  uint32_t difference = currentTime - *getTime(num);

  if (difference < 1000)
    return str(SC_JSON_APS);
  else if (difference < 60000)
    return str(SC_JSON_APS);
  else {
    uint32_t minutes = difference / 60000;

    if (minutes > 60)
      return str(SC_JSON_APS);
    else
      return (String)minutes + str(SC_JSON_APS);
  }
}

bool Stations::getSelected(int num) {
  if (!check(num))
    return false;

  return list->get(num).selected;
}

uint8_t Stations::getCh(int num) {
  if (!check(num))
    return 0;

  return list->get(num).ch;
}

void Stations::select(int num) {
  if (!check(num))
    return;

  internal_select(num);
  prntln(num);
  changed = true;
}

void Stations::deselect(int num) {
  if (!check(num))
    return;

  internal_deselect(num);
  prntln(num);
  changed = true;
}

void Stations::remove(int num) {
  if (!check(num))
    return;

  internal_remove(num);
  prntln(num);
  changed = true;
}

void Stations::select(String ssid) {
  for (int i = 0; i < list->size(); i++) {
    if (getAPStr(i).equalsIgnoreCase(ssid))
      select(i);
  }
}

void Stations::deselect(String ssid) {
  for (int i = 0; i < list->size(); i++) {
    if (getAPStr(i).equalsIgnoreCase(ssid))
      deselect(i);
  }
}

void Stations::remove(String ssid) {
  for (int i = 0; i < list->size(); i++) {
    if (getAPStr(i).equalsIgnoreCase(ssid))
      remove(i);
  }
}

void Stations::selectAll() {
  for (int i = 0; i < count(); i++)
    internal_select(i);
  changed = true;
}

void Stations::deselectAll() {
  for (int i = 0; i < count(); i++)
    internal_deselect(i);
  changed = true;
}

int Stations::count() { return list->size(); }

int Stations::selected() {
  int num = 0;

  for (int i = 0; i < count(); i++)
    if (getSelected(i))
      num++;
  return num;
}

bool Stations::check(int num) {
  if (internal_check(num)) {
    return true;
  } else {
    prntln(num);
    return false;
  }
}

bool Stations::internal_check(int num) { return num >= 0 && num < count(); }

void Stations::internal_select(int num) {
  Station changedStation = list->get(num);

  changedStation.selected = true;
  list->replace(num, changedStation);
}

void Stations::internal_deselect(int num) {
  Station changedStation = list->get(num);

  changedStation.selected = false;
  list->replace(num, changedStation);
}

void Stations::internal_remove(int num) {
  free(getMac(num));
  free(getPkts(num));
  free(getTime(num));
  list->remove(num);
}

void Stations::internal_add(uint8_t *mac, int accesspointNum) {
  if (count() >= STATION_LIST_SIZE)
    removeOldest();

  Station newStation;
  newStation.ap = accesspointNum;
  newStation.ch = wifi_channel;
  newStation.mac = (uint8_t *)malloc(6);
  newStation.pkts = (uint32_t *)malloc(sizeof(uint32_t));
  newStation.time = (uint32_t *)malloc(sizeof(uint32_t));
  newStation.selected = false;

  memcpy(newStation.mac, mac, 6);
  *newStation.pkts = 1;
  *newStation.time = currentTime;

  list->add(newStation);
}

void Stations::internal_removeAll() {
  int c = count();

  for (int i = 0; i < c; i++) {
    free(getMac(i));
    free(getPkts(i));
    free(getTime(i));
  }
  list->clear();
}
