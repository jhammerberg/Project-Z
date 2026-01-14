#include <zephyr/kernel.h>
#include <zephyr/net/wifi_mgmt.h>
#include <zephyr/net/net_if.h>

#include <open62541/server.h>
#include <open62541/server_config_default.h>
#include <open62541/types.h>
#include <open62541/plugin/log_stdout.h>

// Hardcoded for simplicity; in production use a shell or provisioning
#define WIFI_SSID ""
#define WIFI_PSK  ""

static UA_Boolean running = true;

static void connect_wifi(void) {
    struct net_if *iface = net_if_get_default();
    struct wifi_connect_req_params cnx_params = {
        .ssid = WIFI_SSID,
        .ssid_length = strlen(WIFI_SSID),
        .psk = WIFI_PSK,
        .psk_length = strlen(WIFI_PSK),
        .channel = 0,
        .security = WIFI_SECURITY_TYPE_PSK,
    };

    printk("Connecting to Wi-Fi...\n");
    if (net_mgmt(NET_REQUEST_WIFI_CONNECT, iface, &cnx_params, sizeof(cnx_params))) {
        printk("Wi-Fi connection request failed\n");
    } else {
        printk("Wi-Fi connection requested. Waiting for IP...\n");
        // In real code, wait for NET_EVENT_IPV4_ADDR_ADD event here
        k_sleep(K_SECONDS(10)); 
    }
}

static void add_variable(UA_Server *server) {
    /* Define attributes of the variable */
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_Int32 myInteger = 42;
    UA_Variant_setScalar(&attr.value, &myInteger, &UA_TYPES[UA_TYPES_INT32]);
    attr.description = UA_LOCALIZEDTEXT("en-US", "Zephyr Variable");
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "ZephyrVar");
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    /* Add the variable node to the information model */
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, "zephyr.var");
    UA_QualifiedName myIntegerName = UA_QUALIFIEDNAME(1, "ZephyrVar");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);

    UA_Server_addVariableNode(server, myIntegerNodeId, parentNodeId,
                              parentReferenceNodeId, myIntegerName,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                              attr, NULL, NULL);
}

int main(void) {
    k_sleep(K_SECONDS(5)); 
    connect_wifi();

    // Create Server
    UA_Server *server = UA_Server_new();
    UA_ServerConfig *config = UA_Server_getConfig(server);
    
    // Set custom network settings if needed (default usually works with Zephyr sockets)
    UA_ServerConfig_setDefault(config);

    // Add a test variable
    add_variable(server);

    printk("Starting OPC UA Server...\n");

    // Run the server loop. 
    // UA_Server_run uses an internal loop; use run_iterate for non-blocking if needed
    UA_StatusCode retval = UA_Server_run(server, &running);

    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? 0 : 1;
}

int access(const char *pathname, int mode) {
    return -1;
}