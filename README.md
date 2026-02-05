# hashlog

## 1. Objetivos

O sistema deve:
- Preservar a **imutabilidade** dos commits
- Permitir renderização **eficiente** de toda a conversa

## 2. Terminologia

**Commit**  
Nó imutável que contém referência a um commit pai e ao seu conteúdo.

**Thread**  
Caminho lógico de escrita que define onde novos commits são anexados.

**Root Commit**  
Commit ao qual uma thread responde diretamente.

**Head Commit**  
Commit mais recente de uma thread.

**DAG**  
Grafo direcionado acíclico formado pelos commits.

## 3. Modelo de Dados

### 3.1 Commit

```text
Commit {
    id
    blob
    parent
    author
    timestamp
}
```

- Um commit não deve ser modificado após sua criação

### 3.2 Thread

```text
Thread {
    id
    commit
}
```

- O `commit` deve ser o head commit  ser sempre descendente do root commit

## 4. Grafo de Commits

Os commits formam um DAG.

Exemplo:
```
         C6          (thread T2) 
        / 
       V 
C1 <- C2 <- C3 <- C4 (thread T1) 
```

## 5. Índices

### 5.1 children_by_commit

Mapeia commits pais para seus filhos diretos.

parent_commit_id -> [child_commit_ids]

Exemplo
```
C1 -> C2 
C2 -> C3 
C3 -> C4 
C2 -> C6
```

O índice pode ser persistido de forma append-only ou reconstruído a partir dos
commits armazenados.

---

- [X] Criação de commits 
- [X] Criação de blobs
- [X] Criação de threads (branches)
- [ ] Criação de tags leves e tags anotadas 
- [X] Inspeção de objetos (`git cat-file`)
- [ ] ~~Manipulação e inspeção do index (`git update-cache --add` e `git ls-files`)~~
- [X] Manipulação de referências simbólicas
- [X] Listagem de commits (`git log`)
- [ ] Busca pelos melhores ancestrais comuns (`git merge-base`)
- [ ] Revert de um commit, sem resolução de conflitos
- [ ] Status
- [ ] Rebase interativo
- [ ] ~~Stash push, stash pop~~
- [ ] Packfiles