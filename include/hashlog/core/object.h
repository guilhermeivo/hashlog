#ifndef HASHLOG_OBJECT_H
#define HASHLOG_OBJECT_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <hashlog/utils.h>
#include <hashlog/exceptions.h>

#include "core.h"
#include "hash.h"

#define OBJECT_FOLDER "objects"

#define BLOB 0x0
#define TREE 0x1
#define COMMIT 0x2

typedef struct {
    int key;
    char* value;
} keyvalue_t;

extern const keyvalue_t string_type[];

/**
 * @brief Estrutura que representa um objeto no HashLog (semelhante a objetos do Git)
 *
 * Um objeto pode ser de três tipos principais: blob, tree ou commit.
 *
 * - BLOB: contém dados brutos, geralmente texto de um comentário.
 *   Exemplo de conteúdo:
 *     "Este é um comentário de teste"
 *
 * - TREE: representa uma árvore de objetos, armazenando relações pai-filho.
 *   Cada entrada da tree tem o formato:
 *       <nome>\0<hash>
 *     onde:
 *       - nome: identificador do comentário ou arquivo
 *       - hash: hash do objeto filho (blob ou tree)
 *   Exemplo de conteúdo de tree:
 *       blob 1a2b3c4d5e6f7g8h9i0
 *       tree 48jfn10skd10294kxm4
 *       blob 9i8h7g6f5e4d3c2b1a0
 *
 * - COMMIT: representa um snapshot da árvore em determinado ponto no tempo.
 *   Contém referências para:
 *       - tree raiz
 *       - commit pai(s)
 *       - mensagem
 *
 * @note O campo content armazena os dados serializados do objeto.
 *       Para blobs, é o texto do comentário.
 *       Para trees, é a lista de entradas codificada.
 *       Para commits, é o objeto commit serializado (tree, pai, mensagem).
 */
typedef struct {
    int type;
    size_t content_size;
    char* content;
    size_t size;
} hl_object_t;

char* object_string_type(const int type);
int object_define_type(const char* type);
void init_object(hl_object_t* object);
size_t build_object(const hl_object_t* object, char** buffer, const size_t buffer_size);
int write_object(const char* filename, char** content);
hl_object_t read_object(const char* filename);
int load_object(char** buffer, size_t buffer_size, char hex[2 * SHA256_SIZE + 1]);

#endif