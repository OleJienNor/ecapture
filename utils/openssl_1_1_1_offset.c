#include <ctype.h>
#include <stdio.h>
#include <stddef.h>
#include <openssl/crypto.h>

#if defined(SSL_LOCL_H)
#include <ssl/ssl_locl.h>
#else
#include <ssl/ssl_local.h>
#endif

#define SSL_STRUCT_OFFSETS                      \
    X(ssl_st, version)                          \
    X(ssl_st, session)                          \
    X(ssl_st, s3)                               \
    X(ssl_session_st, master_key)               \
    X(ssl3_state_st, client_random)             \
    X(ssl_session_st, cipher)                   \
    X(ssl_session_st, cipher_id)                \
    X(ssl_cipher_st, id)                        \
    X(ssl_st, handshake_secret)                 \
    X(ssl_st, handshake_traffic_hash)           \
    X(ssl_st, client_app_traffic_secret)        \
    X(ssl_st, server_app_traffic_secret)        \
    X(ssl_st, exporter_master_secret)

void toUpper(char *s) {
    int i = 0;
    while (s[i] != '\0') {
        putchar(toupper(s[i]));
        i++;
    }
}

void format(char *struct_name, char *field_name, size_t offset) {
    printf("// %s->%s\n", struct_name, field_name);
    printf("#define ");
    toUpper(struct_name);
    printf("_");
    toUpper(field_name);
    printf(" 0x%lx\n\n", offset);
}

int main() {
    printf("/* OPENSSL_VERSION_TEXT: %s, OPENSSL_VERSION_NUMBER: %ld */\n\n",
           OPENSSL_VERSION_TEXT, OPENSSL_VERSION_NUMBER);

#define X(struct_name, field_name)      \
    format(#struct_name, #field_name, offsetof(struct struct_name, field_name));
    SSL_STRUCT_OFFSETS
#undef X

    return 0;
}