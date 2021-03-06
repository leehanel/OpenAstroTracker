#pragma once

#if HEADLESS_CLIENT == 0
bool processDECKeys() {
  byte key;
  bool waitForRelease = false;
  if (lcdButtons.currentState() == btnUP) {
    if (DECselect == 0) mount.targetDEC().addDegrees(1);
    if (DECselect == 1) mount.targetDEC().addMinutes(1);
    if (DECselect == 2) mount.targetDEC().addSeconds(1);
    // slow down key repetitions
    mount.delay(200);
  }
  else if (lcdButtons.currentState() == btnDOWN) {
    if (DECselect == 0) mount.targetDEC().addDegrees(-1);
    if (DECselect == 1) mount.targetDEC().addMinutes(-1);
    if (DECselect == 2) mount.targetDEC().addSeconds(-1);
    // slow down key repetitions
    mount.delay(200);
  }
  else if (lcdButtons.keyChanged(&key)) {
    waitForRelease = true;
    switch (key)
    {
      case btnLEFT: {
        DECselect = adjustWrap(DECselect, 1, 0, 2);
      }
      break;

      case btnSELECT: {
        if (mount.isSlewingRAorDEC()) {
          mount.stopSlewing(ALL_DIRECTIONS);
        }
        else {
          mount.startSlewingToTarget();
        }
      }
      break;

      case btnRIGHT: {
        lcdMenu.setNextActive();
      }
      break;
    }
  }

  return waitForRelease;
}

void printDECSubmenu() {
  if (mount.isSlewingIdle()) {
    lcdMenu.printMenu(mount.DECString(LCDMENU_STRING | TARGET_STRING, DECselect));
  }
}
#endif
