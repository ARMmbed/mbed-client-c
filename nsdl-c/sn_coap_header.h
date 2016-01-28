/*
 * Copyright (c) 2011-2015 ARM Limited. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * \file sn_coap_header.h
 *
 * \brief CoAP C-library User header interface header file
 */

#ifndef SN_COAP_HEADER_H_
#define SN_COAP_HEADER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Handle structure */
struct coap_s;

/* * * * * * * * * * * * * * */
/* * * * ENUMERATIONS  * * * */
/* * * * * * * * * * * * * * */

/**
 * \brief Enumeration for CoAP Version
 */
typedef enum coap_version_ {
    COAP_VERSION_1          = 0x40,
    COAP_VERSION_UNKNOWN    = 0xFF
} coap_version_e;

/**
 * \brief Enumeration for CoAP Message type, used in CoAP Header
 */
typedef enum sn_coap_msg_type_ {
    COAP_MSG_TYPE_CONFIRMABLE       = 0x00, /**< Reliable Request messages */
    COAP_MSG_TYPE_NON_CONFIRMABLE   = 0x10, /**< Non-reliable Request and Response messages */
    COAP_MSG_TYPE_ACKNOWLEDGEMENT   = 0x20, /**< Response to a Confirmable Request  */
    COAP_MSG_TYPE_RESET             = 0x30  /**< Answer a Bad Request */
} sn_coap_msg_type_e;

/**
 * \brief Enumeration for CoAP Message code, used in CoAP Header
 */
typedef enum sn_coap_msg_code_ {
    COAP_MSG_CODE_EMPTY                                 = 0,
    COAP_MSG_CODE_REQUEST_GET                           = 1,
    COAP_MSG_CODE_REQUEST_POST                          = 2,
    COAP_MSG_CODE_REQUEST_PUT                           = 3,
    COAP_MSG_CODE_REQUEST_DELETE                        = 4,

    COAP_MSG_CODE_RESPONSE_CREATED                      = 65,
    COAP_MSG_CODE_RESPONSE_DELETED                      = 66,
    COAP_MSG_CODE_RESPONSE_VALID                        = 67,
    COAP_MSG_CODE_RESPONSE_CHANGED                      = 68,
    COAP_MSG_CODE_RESPONSE_CONTENT                      = 69,
    COAP_MSG_CODE_RESPONSE_BAD_REQUEST                  = 128,
    COAP_MSG_CODE_RESPONSE_UNAUTHORIZED                 = 129,
    COAP_MSG_CODE_RESPONSE_BAD_OPTION                   = 130,
    COAP_MSG_CODE_RESPONSE_FORBIDDEN                    = 131,
    COAP_MSG_CODE_RESPONSE_NOT_FOUND                    = 132,
    COAP_MSG_CODE_RESPONSE_METHOD_NOT_ALLOWED           = 133,
    COAP_MSG_CODE_RESPONSE_NOT_ACCEPTABLE               = 134,
    COAP_MSG_CODE_RESPONSE_REQUEST_ENTITY_INCOMPLETE    = 136,
    COAP_MSG_CODE_RESPONSE_PRECONDITION_FAILED          = 140,
    COAP_MSG_CODE_RESPONSE_REQUEST_ENTITY_TOO_LARGE     = 141,
    COAP_MSG_CODE_RESPONSE_UNSUPPORTED_CONTENT_FORMAT   = 143,
    COAP_MSG_CODE_RESPONSE_INTERNAL_SERVER_ERROR        = 160,
    COAP_MSG_CODE_RESPONSE_NOT_IMPLEMENTED              = 161,
    COAP_MSG_CODE_RESPONSE_BAD_GATEWAY                  = 162,
    COAP_MSG_CODE_RESPONSE_SERVICE_UNAVAILABLE          = 163,
    COAP_MSG_CODE_RESPONSE_GATEWAY_TIMEOUT              = 164,
    COAP_MSG_CODE_RESPONSE_PROXYING_NOT_SUPPORTED       = 165
} sn_coap_msg_code_e;

/**
 * \brief Enumeration for CoAP Option number, used in CoAP Header
 */
typedef enum sn_coap_option_numbers_ {
    COAP_OPTION_IF_MATCH        = 1,
    COAP_OPTION_URI_HOST        = 3,
    COAP_OPTION_ETAG            = 4,
    COAP_OPTION_IF_NONE_MATCH   = 5,
    COAP_OPTION_OBSERVE         = 6,
    COAP_OPTION_URI_PORT        = 7,
    COAP_OPTION_LOCATION_PATH   = 8,
    COAP_OPTION_URI_PATH        = 11,
    COAP_OPTION_CONTENT_FORMAT  = 12,
    COAP_OPTION_MAX_AGE         = 14,
    COAP_OPTION_URI_QUERY       = 15,
    COAP_OPTION_ACCEPT          = 17,
    COAP_OPTION_LOCATION_QUERY  = 20,
    COAP_OPTION_BLOCK2          = 23,
    COAP_OPTION_BLOCK1          = 27,
    COAP_OPTION_PROXY_URI       = 35,
    COAP_OPTION_PROXY_SCHEME    = 39,
    COAP_OPTION_SIZE1           = 60
//  128 =   (Reserved)
//  132 =   (Reserved)
//  136 =   (Reserved)
} sn_coap_option_numbers_e;

/**
 * \brief Enumeration for CoAP Content Format codes
 */
typedef enum sn_coap_content_format_ {
    COAP_CT_NONE                = -1,
    COAP_CT_TEXT_PLAIN          = 0,
    COAP_CT_LINK_FORMAT         = 40,
    COAP_CT_XML                 = 41,
    COAP_CT_OCTET_STREAM        = 42,
    COAP_CT_EXI                 = 47,
    COAP_CT_JSON                = 50
} sn_coap_content_format_e;

/**
 * \brief Enumeration for CoAP status, used in CoAP Header
 */
typedef enum sn_coap_status_ {
    COAP_STATUS_OK                             = 0, /**< Default value is OK */
    COAP_STATUS_PARSER_ERROR_IN_HEADER         = 1, /**< CoAP will send Reset message to invalid message sender */
    COAP_STATUS_PARSER_DUPLICATED_MSG          = 2, /**< CoAP will send Acknowledgement message to duplicated message sender */
    COAP_STATUS_PARSER_BLOCKWISE_MSG_RECEIVING = 3, /**< User will get whole message after all message blocks received.
                                                         User must release messages with this status. */
    COAP_STATUS_PARSER_BLOCKWISE_ACK           = 4, /**< Acknowledgement for sent Blockwise message received */
    COAP_STATUS_PARSER_BLOCKWISE_MSG_REJECTED  = 5, /**< Blockwise message received but not supported by compiling switch */
    COAP_STATUS_PARSER_BLOCKWISE_MSG_RECEIVED  = 6, /**< Blockwise message fully received and returned to app.
                                                         User must take care of releasing whole payload of the blockwise messages */
    COAP_STATUS_BUILDER_MESSAGE_SENDING_FAILED = 7  /**< When re-transmissions have been done and ACK not received, CoAP library calls
                                                         RX callback with this status */
} sn_coap_status_e;


/* * * * * * * * * * * * * */
/* * * * STRUCTURES  * * * */
/* * * * * * * * * * * * * */

/**
 * \brief Structure for CoAP Options
 */
typedef struct sn_coap_options_list_ {

    uint8_t     max_age_len;        /**< 0-4 bytes. */
    uint8_t    *max_age_ptr;        /**< Must be set to NULL if not used */

    uint16_t    proxy_uri_len;      /**< 1-1034 bytes. */
    uint8_t    *proxy_uri_ptr;      /**< Must be set to NULL if not used */

    uint8_t     etag_len;           /**< 1-8 bytes. Repeatable */
    uint8_t    *etag_ptr;           /**< Must be set to NULL if not used */

    uint16_t    uri_host_len;       /**< 1-255 bytes. */
    uint8_t    *uri_host_ptr;       /**< Must be set to NULL if not used */

    uint16_t    location_path_len;  /**< 0-255 bytes. Repeatable */
    uint8_t    *location_path_ptr;  /**< Must be set to NULL if not used */

    uint8_t     uri_port_len;       /**< 0-2 bytes. */
    uint8_t    *uri_port_ptr;       /**< Must be set to NULL if not used */

    uint16_t    location_query_len; /**< 0-255 bytes. Repeatable */
    uint8_t    *location_query_ptr; /**< Must be set to NULL if not used */

    uint8_t     observe;
    uint8_t     observe_len;        /**< 0-2 bytes. */
    uint8_t    *observe_ptr;        /**< Must be set to NULL if not used */

    uint8_t     accept_len;         /**< 0-2 bytes. Repeatable */
    uint8_t     *accept_ptr;        /**< Must be set to NULL if not used */

    uint16_t    uri_query_len;      /**< 1-255 bytes. Repeatable */
    uint8_t    *uri_query_ptr;      /**< Must be set to NULL if not used */

    uint8_t     block1_len;         /**< 0-3 bytes. */
    uint8_t    *block1_ptr;         /**< Not for User */

    uint8_t     block2_len;         /**< 0-3 bytes. */
    uint8_t    *block2_ptr;         /**< Not for User */
} sn_coap_options_list_s;


/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!! Main CoAP message struct !!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/**
 * \brief Main CoAP message struct
 */
typedef struct sn_coap_hdr_ {
    sn_coap_status_e        coap_status;        /**< Used for telling to User special cases when parsing message */

    /* * * * * * * * * * * */
    /* * * * Header  * * * */
    /* * * * * * * * * * * */

    sn_coap_msg_type_e      msg_type;           /**< Confirmable, Non-Confirmable, Acknowledgement or Reset */
    sn_coap_msg_code_e      msg_code;           /**< Empty: 0; Requests: 1-31; Responses: 64-191 */
    uint16_t                msg_id;             /**< Message ID. Parser sets parsed message ID, builder sets message ID of built coap message */

    /* * * * * * * * * * * */
    /* * * * Options * * * */
    /* * * * * * * * * * * */

    /* Here are most often used Options */

    uint16_t                uri_path_len;       /**< 0-255 bytes. Repeatable. */
    uint8_t                *uri_path_ptr;       /**< Must be set to NULL if not used. E.g: temp1/temp2 */

    uint8_t                 token_len;          /**< 1-8 bytes. */
    uint8_t                *token_ptr;          /**< Must be set to NULL if not used */

    uint8_t                 content_type_len;   /**< 0-2 bytes. */
    uint8_t                *content_type_ptr;   /**< Must be set to NULL if not used */

    /* Here are not so often used Options */
    sn_coap_options_list_s *options_list_ptr;   /**< Must be set to NULL if not used */

    /* * * * * * * * * * * */
    /* * * * Payload * * * */
    /* * * * * * * * * * * */

    uint16_t                payload_len;        /**< Must be set to zero if not used */
    uint8_t                *payload_ptr;        /**< Must be set to NULL if not used */
} sn_coap_hdr_s;

/* * * * * * * * * * * * * * * * * * * * * * */
/* * * * EXTERNAL FUNCTION PROTOTYPES  * * * */
/* * * * * * * * * * * * * * * * * * * * * * */
/**
 * \fn sn_coap_hdr_s *sn_coap_parser(struct coap_s *handle, uint16_t packet_data_len, uint8_t *packet_data_ptr, coap_version_e *coap_version_ptr)
 *
 * \brief Parses CoAP message from given Packet data
 *
 * \param *handle Pointer to CoAP library handle
 *
 * \param packet_data_len is length of given Packet data to be parsed to CoAP message
 *
 * \param *packet_data_ptr is source for Packet data to be parsed to CoAP message
 *
 * \param *coap_version_ptr is destination for parsed CoAP specification version
 *
 * \return Return value is pointer to parsed CoAP message.\n
 *         In following failure cases NULL is returned:\n
 *          -Failure in given pointer (= NULL)\n
 *          -Failure in memory allocation (malloc() returns NULL)
 */
extern sn_coap_hdr_s *sn_coap_parser(struct coap_s *handle, uint16_t packet_data_len, uint8_t *packet_data_ptr, coap_version_e *coap_version_ptr);

/**
 * \fn void sn_coap_parser_release_allocated_coap_msg_mem(struct coap_s *handle, sn_coap_hdr_s *freed_coap_msg_ptr)
 *
 * \brief Releases memory of given CoAP message
 *
 *        Note!!! Does not release Payload part
 *
 * \param *handle Pointer to CoAP library handle
 *
 * \param *freed_coap_msg_ptr is pointer to released CoAP message
 */
extern void sn_coap_parser_release_allocated_coap_msg_mem(struct coap_s *handle, sn_coap_hdr_s *freed_coap_msg_ptr);

/**
 * \fn int16_t sn_coap_builder(uint8_t *dst_packet_data_ptr, sn_coap_hdr_s *src_coap_msg_ptr)
 *
 * \brief Builds an outgoing message buffer from a CoAP header structure.
 *
 * \param *dst_packet_data_ptr is pointer to allocated destination to built CoAP packet
 *
 * \param *src_coap_msg_ptr is pointer to source structure for building Packet data 
 *
 * \return Return value is byte count of built Packet data. In failure cases:\n
 *          -1 = Failure in given CoAP header structure\n
 *          -2 = Failure in given pointer (= NULL)
 */
extern int16_t sn_coap_builder(uint8_t *dst_packet_data_ptr, sn_coap_hdr_s *src_coap_msg_ptr);

/**
 * \fn uint16_t sn_coap_builder_calc_needed_packet_data_size(sn_coap_hdr_s *src_coap_msg_ptr)
 *
 * \brief Calculates needed Packet data memory size for given CoAP message
 *
 * \param *src_coap_msg_ptr is pointer to data which needed Packet
 *          data length is calculated 
 *
 * \return Return value is count of needed memory as bytes for build Packet data
 *          Null if failed
 */
extern uint16_t sn_coap_builder_calc_needed_packet_data_size(sn_coap_hdr_s *src_coap_msg_ptr);

/**
 * \fn int16_t sn_coap_builder_2(uint8_t *dst_packet_data_ptr, sn_coap_hdr_s *src_coap_msg_ptr,  uint16_t blockwise_size)
 *
 * \brief Builds an outgoing message buffer from a CoAP header structure.
 *
 * \param *dst_packet_data_ptr is pointer to allocated destination to built CoAP packet
 *
 * \param *src_coap_msg_ptr is pointer to source structure for building Packet data
 *
 * \param blockwise_payload_size Blockwise message maximum payload size
 *
 * \return Return value is byte count of built Packet data. In failure cases:\n
 *          -1 = Failure in given CoAP header structure\n
 *          -2 = Failure in given pointer (= NULL)
 */
extern int16_t sn_coap_builder_2(uint8_t *dst_packet_data_ptr, sn_coap_hdr_s *src_coap_msg_ptr, uint16_t blockwise_payload_size);

/**
 * \fn uint16_t sn_coap_builder_calc_needed_packet_data_size_2(sn_coap_hdr_s *src_coap_msg_ptr, uint16_t blockwise_payload_size)
 *
 * \brief Calculates needed Packet data memory size for given CoAP message
 *
 * \param *src_coap_msg_ptr is pointer to data which needed Packet
 *          data length is calculated
 * \param blockwise_payload_size Blockwise message maximum payload size
 *
 * \return Return value is count of needed memory as bytes for build Packet data
 *          Null if failed
 */
extern uint16_t sn_coap_builder_calc_needed_packet_data_size_2(sn_coap_hdr_s *src_coap_msg_ptr, uint16_t blockwise_payload_size);

/**
 * \fn sn_coap_hdr_s *sn_coap_build_response(struct coap_s *handle, sn_coap_hdr_s *coap_packet_ptr, uint8_t msg_code)
 *
 * \brief Prepares generic response packet from a request packet. This function allocates memory for the resulting sn_coap_hdr_s
 *
 * \param *handle Pointer to CoAP library handle
 * \param *coap_packet_ptr The request packet pointer
 * \param msg_code response messages code
 *
 * \return *coap_packet_ptr The allocated and pre-filled response packet pointer
 *          NULL    Error in parsing the request
 *
 */
extern sn_coap_hdr_s *sn_coap_build_response(struct coap_s *handle, sn_coap_hdr_s *coap_packet_ptr, uint8_t msg_code);

#ifdef __cplusplus
}
#endif

#endif /* SN_COAP_HEADER_H_ */
