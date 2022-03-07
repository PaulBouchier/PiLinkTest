#pragma once

// esp32 Rx packet IDs (message types received by esp32)
const char pktIdPing = 0;
const char pktIdDriveMotorsRqst = 1;
const char pktIdLogLevel = 2;
const char pktIdReboot = 3;
const char pktIdBITMode = 4;


// esp32 Tx packet IDs (message types sent by esp32)
const char pktIdPong = 0;
const char pktIdOdometry = 1;
const char pktIdLog = 2;
const char pktIdPlatformData = 3;
