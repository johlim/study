#include <dbus/dbus.h>
#include <iostream>

int main()
{
    DBusError err;
    DBusConnection* conn;
    DBusMessage* msg;
    DBusMessage* reply;
    DBusMessageIter args;
    bool stat;
    const char* reply_str;

    dbus_error_init(&err);

    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (dbus_error_is_set(&err))
    {
        std::cerr << "Connection Error (" << err.message << ")" << std::endl;
        dbus_error_free(&err);
        return 1;
    }

    msg = dbus_message_new_method_call(
        "com.example.DBusSample",  // destination (service name)
        "/",                       // object path
        "com.example.DBusInterface", // interface name
        "Hello");                  // method name

    if (msg == nullptr)
    {
        std::cerr << "Message Null" << std::endl;
        return 1;
    }

    reply = dbus_connection_send_with_reply_and_block(conn, msg, -1, &err);
    dbus_message_unref(msg);

    if (dbus_error_is_set(&err))
    {
        std::cerr << "Error in call (" << err.message << ")" << std::endl;
        dbus_error_free(&err);
        return 1;
    }
    if (reply == nullptr)
    {
        std::cerr << "Reply Null" << std::endl;
        return 1;
    }

    if (!dbus_message_iter_init(reply, &args))
    {
        std::cerr << "Reply has no arguments!" << std::endl;
    }
    else if (DBUS_TYPE_STRING != dbus_message_iter_get_arg_type(&args))
    {
        std::cerr << "Argument is not string!" << std::endl;
    }
    else
    {
        dbus_message_iter_get_basic(&args, &reply_str);
        std::cout << "Reply from server: " << reply_str << std::endl;
    }

    dbus_message_unref(reply);
    return 0;
}
