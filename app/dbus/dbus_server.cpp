#include <dbus/dbus.h>
#include <iostream>
#include <cstring>
#include <unistd.h>

void reply_to_method_call(DBusConnection* conn, DBusMessage* msg)
{
    DBusMessage* reply;
    DBusMessageIter args;
    bool stat = true;
    const char* param = "Hello from server";

    reply = dbus_message_new_method_return(msg);
    dbus_message_iter_init_append(reply, &args);
    if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &param))
    {
        std::cerr << "Out of Memory!" << std::endl;
        exit(1);
    }

    if (!dbus_connection_send(conn, reply, NULL))
    {
        std::cerr << "Out of Memory!" << std::endl;
        exit(1);
    }
    dbus_connection_flush(conn);
    dbus_message_unref(reply);
}

int main()
{
    DBusError err;
    DBusConnection* conn;
    int ret;
    DBusMessage* msg;

    dbus_error_init(&err);

    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (dbus_error_is_set(&err))
    {
        std::cerr << "Connection Error (" << err.message << ")" << std::endl;
        dbus_error_free(&err);
        return 1;
    }
    if (conn == nullptr)
    {
        std::cerr << "Connection Null" << std::endl;
        return 1;
    }

    ret = dbus_bus_request_name(conn, "com.example.DBusSample", DBUS_NAME_FLAG_REPLACE_EXISTING , &err);
    if (dbus_error_is_set(&err))
    {
        std::cerr << "Name Error (" << err.message << ")" << std::endl;
        dbus_error_free(&err);
        return 1;
    }
    if (ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER)
    {
        std::cerr << "Not Primary Owner, exiting." << std::endl;
        return 1;
    }

    std::cout << "Service Running ... waiting for method calls." << std::endl;

    while (true)
    {
        dbus_connection_read_write(conn, 0);
        msg = dbus_connection_pop_message(conn);

        if (msg == nullptr)
        {
            usleep(100000);
            continue;
        }

        if (dbus_message_is_method_call(msg, "com.example.DBusInterface", "Hello"))
        {
            reply_to_method_call(conn, msg);
        }

        dbus_message_unref(msg);
    }

    return 0;
}
