# hashlog

## 1. Dependências

```bash
sudo apt install libconfuse-dev
```

## 2. Compilação

```bash
make
```

O binário será gerado no diretório `bin/`.

```bash
./hashlog help
```

## 3. Pendências

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