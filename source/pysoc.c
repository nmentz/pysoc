/**
 *  This is free and unencumbered software released into the public domain.
 *
 *  Anyone is free to copy, modify, publish, use, compile, sell, or
 *  distribute this software, either in source code form or as a compiled
 *  binary, for any purpose, commercial or non-commercial, and by any
 *  means.
 *
 *  In jurisdictions that recognize copyright laws, the author or authors
 *  of this software dedicate any and all copyright interest in the
 *  software to the public domain. We make this dedication for the benefit
 *  of the public at large and to the detriment of our heirs and
 *  successors. We intend this dedication to be an overt act of
 *  relinquishment in perpetuity of all present and future rights to this
 *  software under copyright law.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 *
 *  For more information, please refer to <http://unlicense.org/>
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef _WIN32 
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else // assume linux or macos
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>

////////////////// begin methods /////////////////

static PyObject* tcpSock4 (PyObject* self, PyObject* args) {
#ifdef _WIN32
    const char* address;
    int port;

    if (!PyArg_ParseTuple(args, "si", &address, &port))
        return NULL;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return PyErr_SetFromWindowsErr(WSAGetLastError());

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        WSACleanup();
        return PyErr_SetFromWindowsErr(WSAGetLastError());
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    inet_pton(AF_INET, address, &server.sin_addr);

    if ((connect(sock, (struct sockaddr*)&server, sizeof(server))) < 0) {
        closesocket(sock);
        WSACleanup();
        return PyErr_SetFromWindowsErr(WSAGetLastError());
    }

    return PyLong_FromUnsignedLong(sock);
#else
// linux/macos socket
#endif
}

static PyObject* tcpSock6 (PyObject* self) {
#ifdef _WIN32
// windows socket
#else
// linux/macos socket
#endif
}

static PyObject* kill_socket (PyObject* self, PyObject* args) {
#ifdef _WIN32
    unsigned long sock;

    if (!PyArg_ParseTuple(args, "k", &sock))
        return NULL;

    if (closesocket((SOCKET)sock) == SOCKET_ERROR)
        return PyErr_SetFromWindowsErr(WSAGetLastError());

    WSACleanup();
#else
// linux/macos socket
#endif
    Py_RETURN_NONE;
}

////////////////// end methods ////////////////////

static PyMethodDef pysocMethods[] = {
    {"tcpSock4", (PyCFunction)tcpSock4, METH_VARARGS, "Create an IPv4 TCP socket."},
    {"tcpSock6", (PyCFunction)tcpSock6, METH_NOARGS, "Create an IPv6 TCP socket."},
    {"kill_socket", (PyCFunction)kill_socket, METH_VARARGS, "Close socket."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef pysoc = {
    PyModuleDef_HEAD_INIT,
    "pysoc",
    NULL,
    -1,
    pysocMethods
};

PyMODINIT_FUNC PyInit_pysoc(void) {
    return PyModule_Create(&pysoc);
}
