/******************************************************************************

 @file       simple_gatt_profile.c

 @brief This file contains the Simple GATT profile sample GATT service profile
        for use with the BLE sample application.

 Group: CMCU, SCS
 Target Device: CC2640R2

 ******************************************************************************
 
 Copyright (c) 2010-2018, Texas Instruments Incorporated
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 *  Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

 *  Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 *  Neither the name of Texas Instruments Incorporated nor the names of
    its contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ******************************************************************************
 Release Name: simplelink_cc2640r2_sdk_02_20_00_49
 Release Date: 2018-07-16 13:19:56
 *****************************************************************************/

/*********************************************************************
 * INCLUDES
 */
#include <string.h>
#include <icall.h>
#include "util.h"
/* This Header file contains all BLE API and icall structure definition */
#include "icall_ble_api.h"

#include "simple_gatt_profile.h"

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

#define SERVAPP_NUM_ATTR_SUPPORTED        31//35//30//21//33//17
gattAttribute_t simpleProfileAttrTbl[SERVAPP_NUM_ATTR_SUPPORTED];
/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */
// Simple GATT Profile Service UUID: 0xFFF0
CONST uint8 simpleProfileServUUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(SIMPLEPROFILE_SERV_UUID), HI_UINT16(SIMPLEPROFILE_SERV_UUID)
  //TI_BASE_UUID_128(SIMPLEPROFILE_SERV_UUID)
};

//// Characteristic 1 UUID: 0xFFF1
//CONST uint8 simpleProfilechar1UUID[ATT_BT_UUID_SIZE] =
//{
//  LO_UINT16(SIMPLEPROFILE_CHAR1_UUID), HI_UINT16(SIMPLEPROFILE_CHAR1_UUID)
//  //TI_BASE_UUID_128(SIMPLEPROFILE_CHAR1_UUID)
//};

// Characteristic 2 UUID: 0xFFF2
//CONST uint8 simpleProfilechar2UUID[ATT_BT_UUID_SIZE] =
//{
//  LO_UINT16(SIMPLEPROFILE_CHAR2_UUID), HI_UINT16(SIMPLEPROFILE_CHAR2_UUID)
//};

// Characteristic 3 UUID: 0xFFF3
//CONST uint8 simpleProfilechar3UUID[ATT_BT_UUID_SIZE] =
//{
//  LO_UINT16(SIMPLEPROFILE_CHAR3_UUID), HI_UINT16(SIMPLEPROFILE_CHAR3_UUID)
//};

// Characteristic 4 UUID: 0xFFF4
//CONST uint8 simpleProfilechar4UUID[ATT_BT_UUID_SIZE] =
//{
//  LO_UINT16(SIMPLEPROFILE_CHAR4_UUID), HI_UINT16(SIMPLEPROFILE_CHAR4_UUID)
//};
//
//// Characteristic 5 UUID: 0xFFF5
//CONST uint8 simpleProfilechar5UUID[ATT_BT_UUID_SIZE] =
//{
//  LO_UINT16(SIMPLEPROFILE_CHAR5_UUID), HI_UINT16(SIMPLEPROFILE_CHAR5_UUID)
//};
// Characteristic 6 UUID: 0xFFF6
CONST uint8 simpleProfilechar6UUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(SIMPLEPROFILE_CHAR6_UUID), HI_UINT16(SIMPLEPROFILE_CHAR6_UUID)
};
// Characteristic 7 UUID: 0xFFF7
CONST uint8 simpleProfilechar7UUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(SIMPLEPROFILE_CHAR7_UUID), HI_UINT16(SIMPLEPROFILE_CHAR7_UUID)
};
// Characteristic 8 UUID: 0xFFF8
CONST uint8 simpleProfilechar8UUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(SIMPLEPROFILE_CHAR8_UUID), HI_UINT16(SIMPLEPROFILE_CHAR8_UUID)
};
// Characteristic 9 UUID: 0xFFF9
CONST uint8 simpleProfilechar9UUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(SIMPLEPROFILE_CHAR9_UUID), HI_UINT16(SIMPLEPROFILE_CHAR9_UUID)
};
// Characteristic 10 UUID: 0xFFFA
CONST uint8 simpleProfilechar10UUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(SIMPLEPROFILE_CHAR10_UUID), HI_UINT16(SIMPLEPROFILE_CHAR10_UUID)
};
/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */

static simpleProfileCBs_t *simpleProfile_AppCBs = NULL;

/*********************************************************************
 * Profile Attributes - variables
 */

// Simple Profile Service attribute
static CONST gattAttrType_t simpleProfileService = { ATT_BT_UUID_SIZE, simpleProfileServUUID };


// Simple Profile Characteristic 1 Properties
static uint8 simpleProfileChar1Props = GATT_PROP_READ | GATT_PROP_WRITE;

// Characteristic 1 Value
static uint8 simpleProfileChar1 = 0;

// Simple Profile Characteristic 1 User Description
static uint8 simpleProfileChar1UserDesp[17] = "Characteristic 1";


// Simple Profile Characteristic 2 Properties
static uint8 simpleProfileChar2Props = GATT_PROP_READ;

// Characteristic 2 Value
static uint8 simpleProfileChar2 = 0;

// Simple Profile Characteristic 2 User Description
static uint8 simpleProfileChar2UserDesp[17] = "Characteristic 2";


// Simple Profile Characteristic 3 Properties
static uint8 simpleProfileChar3Props = GATT_PROP_WRITE;

// Characteristic 3 Value
static uint8 simpleProfileChar3 = 0;

// Simple Profile Characteristic 3 User Description
static uint8 simpleProfileChar3UserDesp[17] = "Characteristic 3";


// Simple Profile Characteristic 4 Properties
static uint8 simpleProfileChar4Props = GATT_PROP_NOTIFY;

// Characteristic 4 Value
static uint8 simpleProfileChar4 = 0;

// Simple Profile Characteristic 4 Configuration Each client has its own
// instantiation of the Client Characteristic Configuration. Reads of the
// Client Characteristic Configuration only shows the configuration for
// that client and writes only affect the configuration of that client.
static gattCharCfg_t *simpleProfileChar4Config;

// Simple Profile Characteristic 4 User Description
static uint8 simpleProfileChar4UserDesp[17] = "Characteristic 4";


// Simple Profile Characteristic 5 Properties
static uint8 simpleProfileChar5Props = GATT_PROP_READ;

// Characteristic 5 Value
static uint8 simpleProfileChar5[SIMPLEPROFILE_CHAR5_LEN] = { 0, 0, 0, 0, 0 };

// Simple Profile Characteristic 5 User Description
static uint8 simpleProfileChar5UserDesp[17] = "Characteristic 5";



//status
static uint8 simpleProfileChar6Props = GATT_PROP_READ|GATT_PROP_NOTIFY;
static gattCharCfg_t *simpleProfileChar6Config;
static uint8 simpleProfileChar6UserDesp[23] = "status Characteristic \0";
uint8 DigitalkeyServicestatus = 0;

//info
static uint8 simpleProfileChar7Props = GATT_PROP_READ | GATT_PROP_WRITE|GATT_PROP_NOTIFY;
static gattCharCfg_t *simpleProfileChar7Config;
static uint8 simpleProfileChar7[SIMPLEPROFILE_INFO_LEN] = {0};
static uint8 simpleProfileChar7UserDesp[21] = "info Characteristic \0";
static uint8 DigitalkeyServiceinfolen = 0;

//auth
static uint8 simpleProfileChar8Props = GATT_PROP_WRITE;
static uint8 simpleProfileChar8[SIMPLEPROFILE_AUTH_LEN] = {0};
static uint8 simpleProfileChar8UserDesp[21] = "auth Characteristic \0";
static uint8 DigitalkeyServiceauthlen = 0;

//session
static uint8 simpleProfileChar9Props = GATT_PROP_WRITE|GATT_PROP_NOTIFY;
static uint8 simpleProfileChar9[SIMPLEPROFILE_SESSION_LEN] = {0};
static gattCharCfg_t *simpleProfileChar9Config;
static uint8 simpleProfileChar9UserDesp[28] = "session Characteristic \0";
static uint8 DigitalkeyServicesessionlen = 0;

//cmd
static uint8 simpleProfileChar10Props = GATT_PROP_WRITE|GATT_PROP_NOTIFY;
static uint8 simpleProfileChar10[SIMPLEPROFILE_CMD_LEN] = {0};
static gattCharCfg_t *simpleProfileChar10Config;
static uint8 simpleProfileChar10UserDesp[21] = "cmd Characteristic \0";
static uint8 DigitalkeyServicecmdlen = 0;

/*********************************************************************
 * Profile Attributes - Table
 */

static gattAttribute_t simpleProfileAttrTbl[SERVAPP_NUM_ATTR_SUPPORTED] =
{
  // Simple Profile Service
  {
    { ATT_BT_UUID_SIZE, primaryServiceUUID }, /* type */
    GATT_PERMIT_READ | GATT_PERMIT_WRITE,                         /* permissions */
    0,                                        /* handle */
    (uint8 *)&simpleProfileService            /* pValue */
  },
//
//    // Characteristic 1 Declaration
//    {
//      { ATT_BT_UUID_SIZE, characterUUID },
//      GATT_PERMIT_READ,
//      0,
//      &simpleProfileChar1Props
//    },

//      // Characteristic Value 1
//      {
//        { ATT_BT_UUID_SIZE, simpleProfilechar1UUID },
//        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
//        0,
//        &simpleProfileChar1
//      },

      // Characteristic 1 User Description
//      {
//        { ATT_BT_UUID_SIZE, charUserDescUUID },
//        GATT_PERMIT_READ,
//        0,
//        simpleProfileChar1UserDesp
//      },
//
//    // Characteristic 2 Declaration
//    {
//      { ATT_BT_UUID_SIZE, characterUUID },
//      GATT_PERMIT_READ,
//      0,
//      &simpleProfileChar2Props
//    },

      // Characteristic Value 2
//      {
//        { ATT_BT_UUID_SIZE, simpleProfilechar2UUID },
//        GATT_PERMIT_READ,
//        0,
//        &simpleProfileChar2
//      },

      // Characteristic 2 User Description
//      {
//        { ATT_BT_UUID_SIZE, charUserDescUUID },
//        GATT_PERMIT_READ,
//        0,
//        simpleProfileChar2UserDesp
//      },

    // Characteristic 3 Declaration
//    {
//      { ATT_BT_UUID_SIZE, characterUUID },
//      GATT_PERMIT_READ,
//      0,
//      &simpleProfileChar3Props
//    },
//
//      // Characteristic Value 3
//      {
//        { ATT_BT_UUID_SIZE, simpleProfilechar3UUID },
//        GATT_PERMIT_WRITE,
//        0,
//        &simpleProfileChar3
//      },
//
//      // Characteristic 3 User Description
//      {
//        { ATT_BT_UUID_SIZE, charUserDescUUID },
//        GATT_PERMIT_READ,
//        0,
//        simpleProfileChar3UserDesp
//      },

    // Characteristic 4 Declaration
//    {
//      { ATT_BT_UUID_SIZE, characterUUID },
//      GATT_PERMIT_READ,
//      0,
//      &simpleProfileChar4Props
//    },
//
//      // Characteristic Value 4
//      {
//        { ATT_BT_UUID_SIZE, simpleProfilechar4UUID },
//        0,
//        0,
//        &simpleProfileChar4
//      },
//
//      // Characteristic 4 configuration
//      {
//        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
//        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
//        0,
//        (uint8 *)&simpleProfileChar4Config
//      },
//
//      // Characteristic 4 User Description
//      {
//        { ATT_BT_UUID_SIZE, charUserDescUUID },
//        GATT_PERMIT_READ,
//        0,
//        simpleProfileChar4UserDesp
//      },
//
//    // Characteristic 5 Declaration
//    {
//      { ATT_BT_UUID_SIZE, characterUUID },
//      GATT_PERMIT_READ,
//      0,
//      &simpleProfileChar5Props
//    },
//
//      // Characteristic Value 5
//      {
//        { ATT_BT_UUID_SIZE, simpleProfilechar5UUID },
//        GATT_PERMIT_AUTHEN_READ,
//        0,
//        simpleProfileChar5
//      },
//
//      // Characteristic 5 User Description
//      {
//        { ATT_BT_UUID_SIZE, charUserDescUUID },
//        GATT_PERMIT_READ,
//        0,
//        simpleProfileChar5UserDesp
//      },
////////////////////////////////////////////////////////////////////////////
//status    4
      // Characteristic 6 Declaration
         {
           { ATT_BT_UUID_SIZE, characterUUID },
           GATT_PERMIT_READ,
           0,
           &simpleProfileChar6Props
         },

       // Characteristic Value 6
       {
         { ATT_BT_UUID_SIZE, simpleProfilechar6UUID },
         GATT_PERMIT_READ | GATT_PERMIT_WRITE,
         0,
         &DigitalkeyServicestatus
       },
       // Characteristic 6 configuration
       {
         { ATT_BT_UUID_SIZE, clientCharCfgUUID },
         GATT_PERMIT_READ | GATT_PERMIT_WRITE,
         0,
         (uint8 *)&simpleProfileChar6Config
       },
       // Characteristic 6 User Description
       {
         { ATT_BT_UUID_SIZE, charUserDescUUID },
         GATT_PERMIT_READ,
         0,
         simpleProfileChar6UserDesp
       },
////////////////////////////////////////////////////////////////////////////
//info  3
   // Characteristic 7 Declaration
      {
        { ATT_BT_UUID_SIZE, characterUUID },
        GATT_PERMIT_READ,
        0,
        &simpleProfileChar7Props
      },

        // Characteristic Value 7
        {
          { ATT_BT_UUID_SIZE, simpleProfilechar7UUID },
          GATT_PERMIT_READ | GATT_PERMIT_WRITE,
          0,
          //&simpleProfileChar7
          simpleProfileChar7
        },
        // Characteristic 7 configuration
        {
          { ATT_BT_UUID_SIZE, clientCharCfgUUID },
          GATT_PERMIT_READ | GATT_PERMIT_WRITE,
          0,
          (uint8 *)&simpleProfileChar7Config
        },
        // Characteristic 7 User Description
        {
          { ATT_BT_UUID_SIZE, charUserDescUUID },
          GATT_PERMIT_READ,
          0,
          simpleProfileChar7UserDesp
        },
////////////////////////////////////////////////////////////////////////////
//auth 3
    // Characteristic 8 Declaration
       {
         { ATT_BT_UUID_SIZE, characterUUID },
         GATT_PERMIT_READ,
         0,
         &simpleProfileChar8Props
       },

         // Characteristic Value 8
         {
           { ATT_BT_UUID_SIZE, simpleProfilechar8UUID },
           GATT_PERMIT_READ | GATT_PERMIT_WRITE,
           0,
           //&simpleProfileChar8
           simpleProfileChar8
         },

         // Characteristic 8 User Description
         {
           { ATT_BT_UUID_SIZE, charUserDescUUID },
           GATT_PERMIT_READ,
           0,
           simpleProfileChar8UserDesp
         },
////////////////////////////////////////////////////////////////////////////
//session  4
     // Characteristic 9 Declaration
        {
          { ATT_BT_UUID_SIZE, characterUUID },
          GATT_PERMIT_READ,
          0,
          &simpleProfileChar9Props
        },

          // Characteristic Value 9
          {
            { ATT_BT_UUID_SIZE, simpleProfilechar9UUID },
            GATT_PERMIT_READ | GATT_PERMIT_WRITE,
            0,
            //&simpleProfileChar9
            simpleProfileChar9
          },
          // Characteristic 9 configuration
          {
            { ATT_BT_UUID_SIZE, clientCharCfgUUID },
            GATT_PERMIT_READ | GATT_PERMIT_WRITE,
            0,
            (uint8 *)&simpleProfileChar9Config
          },
          // Characteristic 9 User Description
          {
            { ATT_BT_UUID_SIZE, charUserDescUUID },
            GATT_PERMIT_READ,
            0,
            simpleProfileChar9UserDesp
          },
////////////////////////////////////////////////////////////////////////////
//cmd   4
          // Characteristic 10 Declaration
          {
            { ATT_BT_UUID_SIZE, characterUUID },
            GATT_PERMIT_READ,
            0,
            &simpleProfileChar10Props
          },

            // Characteristic Value 10
            {
              { ATT_BT_UUID_SIZE, simpleProfilechar10UUID },
              GATT_PERMIT_WRITE,
              0,
              //&simpleProfileChar10
              simpleProfileChar10
            },

            // Characteristic 10 configuration
              {
                { ATT_BT_UUID_SIZE, clientCharCfgUUID },
                GATT_PERMIT_READ | GATT_PERMIT_WRITE,
                0,
                (uint8 *)&simpleProfileChar10Config
              },

            // Characteristic 10 User Description
            {
              { ATT_BT_UUID_SIZE, charUserDescUUID },
              GATT_PERMIT_READ,
              0,
              simpleProfileChar10UserDesp
            },
};

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static bStatus_t simpleProfile_ReadAttrCB(uint16_t connHandle,
                                          gattAttribute_t *pAttr,
                                          uint8_t *pValue, uint16_t *pLen,
                                          uint16_t offset, uint16_t maxLen,
                                          uint8_t method);
static bStatus_t simpleProfile_WriteAttrCB(uint16_t connHandle,
                                           gattAttribute_t *pAttr,
                                           uint8_t *pValue, uint16_t len,
                                           uint16_t offset, uint8_t method);

/*********************************************************************
 * PROFILE CALLBACKS
 */

// Simple Profile Service Callbacks
// Note: When an operation on a characteristic requires authorization and
// pfnAuthorizeAttrCB is not defined for that characteristic's service, the
// Stack will report a status of ATT_ERR_UNLIKELY to the client.  When an
// operation on a characteristic requires authorization the Stack will call
// pfnAuthorizeAttrCB to check a client's authorization prior to calling
// pfnReadAttrCB or pfnWriteAttrCB, so no checks for authorization need to be
// made within these functions.
CONST gattServiceCBs_t simpleProfileCBs =
{
  simpleProfile_ReadAttrCB,  // Read callback function pointer
  simpleProfile_WriteAttrCB, // Write callback function pointer
  NULL                       // Authorization callback function pointer
};

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      SimpleProfile_AddService
 *
 * @brief   Initializes the Simple Profile service by registering
 *          GATT attributes with the GATT server.
 *
 * @param   services - services to add. This is a bit map and can
 *                     contain more than one service.
 *
 * @return  Success or Failure
 */
bStatus_t SimpleProfile_AddService( uint32 services )
{
  uint8 status;

  // Allocate Client Characteristic Configuration table
  simpleProfileChar4Config = (gattCharCfg_t *)ICall_malloc( sizeof(gattCharCfg_t) *
                                                            MAX_NUM_BLE_CONNS );
  if ( simpleProfileChar4Config == NULL )
  {
    return ( bleMemAllocError );
  }
  simpleProfileChar6Config = (gattCharCfg_t *)ICall_malloc( sizeof(gattCharCfg_t) *
                                                            MAX_NUM_BLE_CONNS );
  if ( simpleProfileChar6Config == NULL )
  {
    return ( bleMemAllocError );
  }
  simpleProfileChar7Config = (gattCharCfg_t *)ICall_malloc( sizeof(gattCharCfg_t) *
                                                            MAX_NUM_BLE_CONNS );
  if ( simpleProfileChar7Config == NULL )
  {
    return ( bleMemAllocError );
  }
  simpleProfileChar9Config = (gattCharCfg_t *)ICall_malloc( sizeof(gattCharCfg_t) *
                                                            MAX_NUM_BLE_CONNS );
  if ( simpleProfileChar9Config == NULL )
  {
    return ( bleMemAllocError );
  }

  simpleProfileChar10Config = (gattCharCfg_t *)ICall_malloc( sizeof(gattCharCfg_t) *
                                                            MAX_NUM_BLE_CONNS );
  if ( simpleProfileChar10Config == NULL )
  {
    return ( bleMemAllocError );
  }

  // Initialize Client Characteristic Configuration attributes
  GATTServApp_InitCharCfg( CONNHANDLE_INVALID, simpleProfileChar4Config );

  GATTServApp_InitCharCfg( CONNHANDLE_INVALID, simpleProfileChar6Config );//status config
  GATTServApp_InitCharCfg( CONNHANDLE_INVALID, simpleProfileChar7Config );//info config
  GATTServApp_InitCharCfg( CONNHANDLE_INVALID, simpleProfileChar9Config );//session config
  GATTServApp_InitCharCfg( CONNHANDLE_INVALID, simpleProfileChar10Config );//cmd config

  if ( services & SIMPLEPROFILE_SERVICE )
  {
    // Register GATT attribute list and CBs with GATT Server App
    status = GATTServApp_RegisterService( simpleProfileAttrTbl,
                                          GATT_NUM_ATTRS( simpleProfileAttrTbl ),
                                          GATT_MAX_ENCRYPT_KEY_SIZE,
                                          &simpleProfileCBs );
  }
  else
  {
    status = SUCCESS;
  }

  return ( status );
}

/*********************************************************************
 * @fn      SimpleProfile_RegisterAppCBs
 *
 * @brief   Registers the application callback function. Only call
 *          this function once.
 *
 * @param   callbacks - pointer to application callbacks.
 *
 * @return  SUCCESS or bleAlreadyInRequestedMode
 */
bStatus_t SimpleProfile_RegisterAppCBs( simpleProfileCBs_t *appCallbacks )
{
  if ( appCallbacks )
  {
    simpleProfile_AppCBs = appCallbacks;

    return ( SUCCESS );
  }
  else
  {
    return ( bleAlreadyInRequestedMode );
  }
}

/*********************************************************************
 * @fn      SimpleProfile_SetParameter
 *
 * @brief   Set a Simple Profile parameter.
 *
 * @param   param - Profile parameter ID
 * @param   len - length of data to write
 * @param   value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 *
 * @return  bStatus_t
 */
bStatus_t SimpleProfile_SetParameter( uint8 param, uint8 len, void *value )
{
  bStatus_t ret = SUCCESS;
  switch ( param )
  {
//    case SIMPLEPROFILE_CHAR1:
//      if ( len == sizeof ( uint8 ) )
//      {
//        simpleProfileChar1 = *((uint8*)value);
//      }
//      else
//      {
//        ret = bleInvalidRange;
//      }
//      break;

//    case SIMPLEPROFILE_CHAR2:
//      if ( len == sizeof ( uint8 ) )
//      {
//        simpleProfileChar2 = *((uint8*)value);
//      }
//      else
//      {
//        ret = bleInvalidRange;
//      }
//      break;

//    case SIMPLEPROFILE_CHAR3:
//      if ( len == sizeof ( uint8 ) )
//      {
//        simpleProfileChar3 = *((uint8*)value);
//      }
//      else
//      {
//        ret = bleInvalidRange;
//      }
//      break;

//    case SIMPLEPROFILE_CHAR4:
//      if ( len == sizeof ( uint8 ) )
//      {
//        simpleProfileChar4 = *((uint8*)value);
//
//        // See if Notification has been enabled
//        GATTServApp_ProcessCharCfg( simpleProfileChar4Config, &simpleProfileChar4, FALSE,
//                                    simpleProfileAttrTbl, GATT_NUM_ATTRS( simpleProfileAttrTbl ),
//                                    INVALID_TASK_ID, simpleProfile_ReadAttrCB );
//      }
//      else
//      {
//        ret = bleInvalidRange;
//      }
//      break;
//
//    case SIMPLEPROFILE_CHAR5:
//      if ( len == SIMPLEPROFILE_CHAR5_LEN )
//      {
//        VOID memcpy( simpleProfileChar5, value, SIMPLEPROFILE_CHAR5_LEN );
//      }
//      else
//      {
//        ret = bleInvalidRange;
//      }
//      break;
    case SIMPLEPROFILE_CHAR6://status
        if ( len == sizeof ( uint8 ) )
              {
                DigitalkeyServicestatus  = *((uint8*)value);

                // See if Notification has been enabled
                GATTServApp_ProcessCharCfg( simpleProfileChar6Config, &DigitalkeyServicestatus , FALSE,
                                            simpleProfileAttrTbl, GATT_NUM_ATTRS( simpleProfileAttrTbl ),
                                            INVALID_TASK_ID, simpleProfile_ReadAttrCB );
              }
              else
              {
                ret = bleInvalidRange;
              }
      break;
    case SIMPLEPROFILE_CHAR7://info
        if ( len <= SIMPLEPROFILE_INFO_LEN )
              {
                VOID memcpy( simpleProfileChar7, value, len );
                DigitalkeyServiceinfolen=len;
                // See if Notification has been enabled
                                GATTServApp_ProcessCharCfg( simpleProfileChar7Config, &simpleProfileChar7 , FALSE,
                                                            simpleProfileAttrTbl, GATT_NUM_ATTRS( simpleProfileAttrTbl ),
                                                            INVALID_TASK_ID, simpleProfile_ReadAttrCB );
              }
              else
              {
                ret = bleInvalidRange;
              }
      break;
    case SIMPLEPROFILE_CHAR8://auth
      break;
    case SIMPLEPROFILE_CHAR9://session
        if ( len <= SIMPLEPROFILE_SESSION_LEN )
              {
                DigitalkeyServicesessionlen=len;
                //simpleProfileChar9 = *((uint8*)value);
                VOID memcpy(simpleProfileChar9,value, len);

                // See if Notification has been enabled
                GATTServApp_ProcessCharCfg( simpleProfileChar9Config, &simpleProfileChar9, FALSE,
                                            simpleProfileAttrTbl, GATT_NUM_ATTRS( simpleProfileAttrTbl ),
                                            INVALID_TASK_ID, simpleProfile_ReadAttrCB );
              }
              else
              {
                ret = bleInvalidRange;
              }
      break;
    case SIMPLEPROFILE_CHAR10://cmd
        if ( len <= SIMPLEPROFILE_CMD_LEN )
              {
                DigitalkeyServicecmdlen=len;
                VOID memcpy(simpleProfileChar10, value, len );
                //simpleProfileChar10 = *((uint8*)value);

                // See if Notification has been enabled
                GATTServApp_ProcessCharCfg( simpleProfileChar10Config, &simpleProfileChar10, FALSE,
                                            simpleProfileAttrTbl, GATT_NUM_ATTRS( simpleProfileAttrTbl ),
                                            INVALID_TASK_ID, simpleProfile_ReadAttrCB );
              }
              else
              {
                ret = bleInvalidRange;
              }
          break;

    default:
      ret = INVALIDPARAMETER;
      break;
  }

  return ( ret );
}

/*********************************************************************
 * @fn      SimpleProfile_GetParameter
 *
 * @brief   Get a Simple Profile parameter.
 *
 * @param   param - Profile parameter ID
 * @param   value - pointer to data to put.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 *
 * @return  bStatus_t
 */
bStatus_t SimpleProfile_GetParameter( uint8 param, void *value )
{
  bStatus_t ret = SUCCESS;
  switch ( param )
  {
//    case SIMPLEPROFILE_CHAR1:
//      *((uint8*)value) = simpleProfileChar1;
//      break;

//    case SIMPLEPROFILE_CHAR2:
//      *((uint8*)value) = simpleProfileChar2;
//      break;

//    case SIMPLEPROFILE_CHAR3:
//      *((uint8*)value) = simpleProfileChar3;
//      break;

//    case SIMPLEPROFILE_CHAR4:
//      *((uint8*)value) = simpleProfileChar4;
//      break;
//
//    case SIMPLEPROFILE_CHAR5:
//      VOID memcpy( value, simpleProfileChar5, SIMPLEPROFILE_CHAR5_LEN );
//      break;
    case SIMPLEPROFILE_CHAR6://status
      break;
    case SIMPLEPROFILE_CHAR7://info
        VOID memcpy( value, simpleProfileChar7, DigitalkeyServiceinfolen );
        //*returnBytes = DigitalkeyServiceinfolen;
      break;
    case SIMPLEPROFILE_CHAR8://auth
        VOID memcpy( value, simpleProfileChar8, DigitalkeyServiceauthlen );
        //*returnBytes = DigitalkeyServiceauthlen;
      break;
    case SIMPLEPROFILE_CHAR9://session
        VOID memcpy( value, simpleProfileChar9, DigitalkeyServicesessionlen );
        //*returnBytes = DigitalkeyServicesessionlen;
      break;
    case SIMPLEPROFILE_CHAR10://cmd
        VOID memcpy( value, simpleProfileChar10, DigitalkeyServicecmdlen );
        //*returnBytes = DigitalkeyServicecmdlen;
          break;
    default:
      ret = INVALIDPARAMETER;
      break;
  }

  return ( ret );
}

/*********************************************************************
 * @fn          simpleProfile_ReadAttrCB
 *
 * @brief       Read an attribute.
 *
 * @param       connHandle - connection message was received on
 * @param       pAttr - pointer to attribute
 * @param       pValue - pointer to data to be read
 * @param       pLen - length of data to be read
 * @param       offset - offset of the first octet to be read
 * @param       maxLen - maximum length of data to be read
 * @param       method - type of read message
 *
 * @return      SUCCESS, blePending or Failure
 */
static bStatus_t simpleProfile_ReadAttrCB(uint16_t connHandle,
                                          gattAttribute_t *pAttr,
                                          uint8_t *pValue, uint16_t *pLen,
                                          uint16_t offset, uint16_t maxLen,
                                          uint8_t method)
{
  bStatus_t status = SUCCESS;

  // Make sure it's not a blob operation (no attributes in the profile are long)
  if ( offset > 0 )
  {
    return ( ATT_ERR_ATTR_NOT_LONG );
  }

  if ( pAttr->type.len == ATT_BT_UUID_SIZE )
  {
    // 16-bit UUID
    uint16 uuid = BUILD_UINT16( pAttr->type.uuid[0], pAttr->type.uuid[1]);
    switch ( uuid )
    {
      // No need for "GATT_SERVICE_UUID" or "GATT_CLIENT_CHAR_CFG_UUID" cases;
      // gattserverapp handles those reads

      // characteristics 1 and 2 have read permissions
      // characteritisc 3 does not have read permissions; therefore it is not
      //   included here
      // characteristic 4 does not have read permissions, but because it
      //   can be sent as a notification, it is included here
      //case SIMPLEPROFILE_CHAR1_UUID:
      //case SIMPLEPROFILE_CHAR2_UUID:
//      case SIMPLEPROFILE_CHAR4_UUID:
//        *pLen = 1;
//        pValue[0] = *pAttr->pValue;
//        break;
//
//      case SIMPLEPROFILE_CHAR5_UUID:
//        *pLen = SIMPLEPROFILE_CHAR5_LEN;
//        VOID memcpy( pValue, pAttr->pValue, SIMPLEPROFILE_CHAR5_LEN );
//        break;
      case SIMPLEPROFILE_CHAR6_UUID://status
          *pLen = 1;
            pValue[0] = *pAttr->pValue;
            //DEBUG("read.status"); DEBUG((uint8_t*)convInt32ToText((int)pValue[0])); DEBUG_NEWLINE();
        break;
      case SIMPLEPROFILE_CHAR7_UUID://info
/*
          if(true == ifLOG){
                          DEBUG("info_read");DEBUG_NEWLINE();
                      }

                     // if(statem.status == CARINFO_VALID){/*check status if is 0x00 can be readed*/
                          //if(info_t.flag == SUCCESS && info_t.infolen != 0){/*Rely on MTUsize*/
                              //DEBUG("info_t.flag == SUCCESS");DEBUG_NEWLINE();

/*          #ifndef BLE_SCANNER_DEBUG
                              *pLen=info_t.infolen;
                              VOID memcpy(pValue,info_t.info_data,info_t.infolen);
          #else

                              *pLen = VIN_LEN;
                              VOID memcpy(pValue,statem.vin, VIN_LEN);
          #endif
                              DigitalkeyServicestatus=READ_INFO;chanage status to 0x01
                              //DigitalkeyServicestatus=0x80;
                              statem.status=READ_INFO;*/
                              //DEBUG("33333");DEBUG_NEWLINE();
                              //uint8_t status[10] = {0x7E,0x10,0x10,0x02,0xFF,0xF1,0x01,0x01,0xFF,0xFF};
                              //UART_WriteTransport (status, 10);
                         // }
                          //else{
                              //DigitalkeyServicestatus = CARINFO_INVALID;/*chanage status to 0xFF*/
                              //statem.status=CARINFO_INVALID;
                          //}
                      //}

              break;
      case SIMPLEPROFILE_CHAR8_UUID://auth
              break;
      case SIMPLEPROFILE_CHAR9_UUID://session
          *pLen = DigitalkeyServicesessionlen;
          VOID memcpy( pValue, pAttr->pValue, DigitalkeyServicesessionlen );
              break;
      case SIMPLEPROFILE_CHAR10_UUID://cmd
          *pLen = DigitalkeyServicecmdlen;
          VOID memcpy( pValue, pAttr->pValue, DigitalkeyServicecmdlen );
                    break;

      default:
        // Should never get here! (characteristics 3 and 4 do not have read permissions)
        *pLen = 0;
        status = ATT_ERR_ATTR_NOT_FOUND;
        break;
    }
  }
  else
  {
    // 128-bit UUID
    *pLen = 0;
    status = ATT_ERR_INVALID_HANDLE;
  }

  return ( status );
}

/*********************************************************************
 * @fn      simpleProfile_WriteAttrCB
 *
 * @brief   Validate attribute data prior to a write operation
 *
 * @param   connHandle - connection message was received on
 * @param   pAttr - pointer to attribute
 * @param   pValue - pointer to data to be written
 * @param   len - length of data
 * @param   offset - offset of the first octet to be written
 * @param   method - type of write message
 *
 * @return  SUCCESS, blePending or Failure
 */
static bStatus_t simpleProfile_WriteAttrCB(uint16_t connHandle,
                                           gattAttribute_t *pAttr,
                                           uint8_t *pValue, uint16_t len,
                                           uint16_t offset, uint8_t method)
{
  bStatus_t status = SUCCESS;
  uint8 notifyApp = 0xFF;

  if ( pAttr->type.len == ATT_BT_UUID_SIZE )
  {
    // 16-bit UUID
    uint16 uuid = BUILD_UINT16( pAttr->type.uuid[0], pAttr->type.uuid[1]);
    switch ( uuid )
    {
      //case SIMPLEPROFILE_CHAR1_UUID:
//      case SIMPLEPROFILE_CHAR3_UUID:
//
//        //Validate the value
//        // Make sure it's not a blob oper
//        if ( offset == 0 )
//        {
//          if ( len != 1 )
//          {
//            status = ATT_ERR_INVALID_VALUE_SIZE;
//          }
//        }
//        else
//        {
//          status = ATT_ERR_ATTR_NOT_LONG;
//        }
//
//        //Write the value
//        if ( status == SUCCESS )
//        {
//          uint8 *pCurValue = (uint8 *)pAttr->pValue;
//          *pCurValue = pValue[0];
//
////          if( pAttr->pValue == &simpleProfileChar1 )
////          {
////            notifyApp = SIMPLEPROFILE_CHAR1;
////          }
////          else
////          {
////            notifyApp = SIMPLEPROFILE_CHAR3;
////          }
//        }
//
//        break;
      case SIMPLEPROFILE_CHAR6_UUID:
        break;
      case SIMPLEPROFILE_CHAR7_UUID:
              break;
      case SIMPLEPROFILE_CHAR8_UUID:
              break;
      case SIMPLEPROFILE_CHAR9_UUID:
              break;

      case GATT_CLIENT_CHAR_CFG_UUID:

        status = GATTServApp_ProcessCCCWriteReq( connHandle, pAttr, pValue, len,
                                                 offset, GATT_CLIENT_CFG_NOTIFY );
        break;

      default:
        // Should never get here! (characteristics 2 and 4 do not have write permissions)
        status = ATT_ERR_ATTR_NOT_FOUND;
        break;
    }
  }
  else
  {
    // 128-bit UUID
    status = ATT_ERR_INVALID_HANDLE;
  }

  // If a characteristic value changed then callback function to notify application of change
  if ( (notifyApp != 0xFF ) && simpleProfile_AppCBs && simpleProfile_AppCBs->pfnSimpleProfileChange )
  {
    simpleProfile_AppCBs->pfnSimpleProfileChange( notifyApp );
  }

  return ( status );
}

/*********************************************************************
*********************************************************************/
