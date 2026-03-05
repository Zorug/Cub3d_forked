# TODO — Cub3D (estado atualizado)

## ✅ Já resolvido

- [x] Leitura de ficheiro `.cub` sem limite fixo de buffer (migração para `get_next_line` em `src/parsing/parse_file.c`)
- [x] Validação de limites por comprimento real da linha (`ft_strlen(map[y])`) em pontos críticos:
  - `src/utils.c` (`find_player`)
  - `src/render.c` (`draw_minimap`)
  - `src/hooks.c` (`is_walkable`)
  - `src/raycast/raycast.c` (`perform_dda`)
- [x] Correção de cenários com linhas de mapa de comprimentos diferentes

---

## 🔴 Prioridade alta

### 1) Garantir libertação de `scene_config` no fecho
**Ficheiro:** `src/hooks.c`  
**Problema:** `free_scene_config(&data->config);` está comentado em `close_window`.  
**Ação:** reativar a chamada e validar que não há double free.  
**Critério de aceitação:** fecho da app sem leaks de caminhos de textura (`no/so/we/ea`).

### 2) Validar falhas de inicialização da MLX
**Ficheiro:** `src/initialization.c`  
**Problema:** checks de erro para `mlx_init`, `mlx_new_window` e `mlx_new_image` estão comentados.  
**Ação:** tratar retornos `NULL` com `error_exit(...)` e cleanup seguro.  
**Critério de aceitação:** falhas de MLX terminam com mensagem clara e sem crash.

### 3) Reforçar parsing RGB (caracteres inválidos)
**Ficheiro:** `src/parsing/parse_colors.c`  
**Problema:** `ft_atoi` aceita strings parcialmente inválidas (ex.: `12a`, `++1`) e isso pode passar silenciosamente.  
**Ação:** validar formato estrito por componente (apenas dígitos e espaços periféricos), depois converter e validar intervalo `0..255`.  
**Critério de aceitação:** rejeitar `F 220,10x,0`, `C 1,,2`, `C +1,2,3`; aceitar formatos válidos com espaços normais.

### 4) Garantir que o mapa é o último bloco do `.cub`
**Ficheiros:** `src/parsing/parse_file.c`, `src/parsing/parse_map.c`  
**Problema:** após iniciar o mapa, não há validação explícita para impedir linhas de config extra no fim.  
**Ação:** validar que, depois do bloco de mapa, só existem linhas vazias (ou EOF).  
**Critério de aceitação:** ficheiro com textura/cor após o mapa falha com erro explícito.

---

## 🟠 Prioridade média

### 5) Completar `README.md`
**Ficheiro:** `README.md`  
**Estado atual:** muito incompleto.  
**Ação:** documentar build, execução, formato `.cub`, controlos (`WASD`, setas, `M`, `R`, `ESC`) e limitações conhecidas.  
**Critério de aceitação:** utilizador novo consegue compilar e correr sem ajuda externa.

### 6) Adicionar regra `bonus` no `Makefile`
**Ficheiro:** `Makefile`  
**Problema:** não existe target `bonus`.  
**Ação:** incluir target (mesmo que a implementação atual use o mesmo binário) de forma compatível com avaliação.  
**Critério de aceitação:** `make bonus` executa com sucesso e gera saída esperada.

---

## 🟡 Qualidade / conformidade (Norminette)

### 7) Normalizar estilo e naming
**Ficheiros principais:** `inc/cub3d.h`, `src/*.c`, `src/parsing/*.c`, `src/raycast/*.c`  
**Problemas típicos observáveis:**
- variáveis em camelCase (`posX`, `dirY`, `planeX`, etc.)
- comentários `//` em vários ficheiros
- formatação/indentação inconsistente em alguns blocos

**Ação:** plano faseado por módulo para não partir comportamento:
1. `parsing`
2. `render/raycast`
3. `hooks/init/main`
4. `header` e structs

**Critério de aceitação:** `norminette` sem erros nos ficheiros do projeto.

---

## 📌 Ordem de execução recomendada

1. Leak/cleanup (`close_window`)  
2. Tratamento de erros MLX  
3. Validação RGB estrita  
4. Regra “mapa é o último bloco”  
5. `README.md` + `Makefile bonus`  
6. Passagem final de Norminette

---

## 🧪 Checklist de validação rápida

- [ ] `make && ./cub3D maptest.cub`
- [ ] mapa com linhas de comprimentos diferentes continua válido
- [ ] RGB inválido falha com erro (ex.: `F 100,2a,30`)
- [ ] config após mapa falha corretamente
- [ ] fechar janela/ESC sem leaks relevantes
- [ ] `make bonus` funcional
- [ ] `norminette` limpo
