#include "uuid.h"
/*=========================================================================*\ 
 * UUID - Universally Unique Identifier
 *
 * version 1.0 2010/03/01
\*=========================================================================*/

/*
 * Exported functions
 */
static int create(lua_State *L)
{
    uuid_t *uuid;
    uuid_fmt_t fmt;
    size_t len = 0;
    char *str = NULL;
    const char *ch = luaL_checkstring(L, 1);
    int flag = lua_toboolean(L, 2) ? UUID_MAKE_MC : 0;
    if (strncmp(ch, "bin", 3) == 0)
        fmt = UUID_FMT_BIN;
    else if (strncmp(ch, "str", 3) == 0)
        fmt = UUID_FMT_STR;
    else if (strncmp(ch, "txt", 3) == 0)
        fmt = UUID_FMT_TXT;
    else if (strncmp(ch, "siv", 3) == 0)
        fmt = UUID_FMT_SIV;
    else
    {
        lua_pushnil(L);
        lua_pushstring(L, "invalid format");
        return 2;
    }
    
    uuid_create(&uuid);
    uuid_make(uuid, UUID_MAKE_V1 | flag);
    uuid_export(uuid, fmt, &str, &len);
    uuid_destroy(uuid);
    if (fmt == UUID_FMT_BIN)
        lua_pushlstring(L, str, len);
    else
        lua_pushstring(L, str);
    free(str);
    return 1;
}

/*
    TODO Pensar em uma forma alternativa para gerar o hash de um identificador
*/
// static int hash(lua_State *L)
// {
//     uuid_t *hash;
//     uuid_t *uuid;
// 
//     char *str = NULL;
//     
//     const char *uuid_str = luaL_checkstring(L, 1);
//     const char *url = luaL_checkstring(L, 2);
//     
//     uuid_create(&uuid);
//     uuid_import(uuid, UUID_FMT_STR, uuid_str, strlen(uuid_str));
// 
//     uuid_create(&hash);
//     uuid_make(hash, UUID_MAKE_V5, uuid, url);
//     uuid_export(uuid, UUID_FMT_SIV, &str, NULL);
//     uuid_destroy(hash);
//     uuid_destroy(uuid);
//     lua_pushstring(L, str);
//     free(str);
//     return 1;
// }

static int hash(lua_State *L)
{
    
    
    // unsigned char *SHA1(const unsigned char *d, unsigned long n, unsigned char *md);
    unsigned char hash[SHA_DIGEST_LENGTH];
    const char *id = luaL_checkstring(L, 1);
    
    // printf("%s\n", id);
    
    SHA1(id, strlen(id), hash);
    
    // int i;
    // for (i = 0; i < SHA_DIGEST_LENGTH; i++) {
    //     printf("%02x", hash[i]);
    // }
    // printf("\n");

    // return a bit string
    lua_pushstring(L, hash);
    return 1;
}

/*
 * List of the exported functions
 */
static luaL_Reg funcs[] =
{
    {"create", create},
    {"hash", hash},
    {NULL,     NULL}
};

/*
 * Function called by lua to registry the functions of the library
 */
int luaopen_uuid(lua_State *L)
{
    luaL_register(L, "uuid", funcs);
    return 1;
}
