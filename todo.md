# 📋 TODO — Projeto cub3D

## ✅ O QUE ESTÁ FEITO E FUNCIONAL

| Funcionalidade | Estado | Ficheiro(s) |
|---|---|---|
| Parsing do ficheiro `.cub` (texturas, cores, mapa) | ✅ Completo | `src/parsing/parse_file.c`, `parse_textures.c`, `parse_colors.c`, `parse_map.c`, `parse_utils.c` |
| Validação da extensão `.cub` | ✅ | `parse_file.c` |
| Parsing das 4 texturas (NO, SO, WE, EA) | ✅ | `parse_textures.c` |
| Parsing das cores F e C (RGB) | ✅ | `parse_colors.c` |
| Deteção de duplicados (texturas/cores) | ✅ | `parse_textures.c`, `parse_colors.c` |
| Validação do mapa (chars válidos, 1 jogador, mapa fechado) | ✅ | `validate_map.c` |
| Carregamento de texturas XPM | ✅ | `parse_textures.c` |
| Inicialização MLX + janela | ✅ | `initialization.c` |
| Raycasting com DDA | ✅ | `src/raycast/raycast.c`, `init_dda.c` |
| Renderização 3D com texturas nas paredes | ✅ | `render.c` |
| Sombreamento nas paredes laterais (side == 1) | ✅ | `render.c` |
| Cores de chão e teto do ficheiro `.cub` | ✅ | `render.c` (usa `data->config.floor_color` e `ceiling_color`) |
| Movimento WASD | ✅ | `hooks.c` |
| Rotação com setas esquerda/direita | ✅ | `hooks.c` |
| ESC fecha a janela | ✅ | `hooks.c` |
| Fechar pela red cross (X da janela) | ✅ | `initialization.c` (`mlx_hook` evento 17) |
| Minimap | ✅ (Bónus) | `render.c`, `src/raycast/draw_minimap.c` |
| Colisão com paredes | ✅ (Bónus) | `hooks.c` (`is_walkable`) |
| Rotação com rato (toggle M) | ✅ (Bónus) | `hooks.c` (`mouse_move`, `toggle_mouse`) |
| Raios visíveis no minimap (toggle R) | ✅ (Bónus) | `draw_minimap.c` |
| Libertação de memória ao fechar | ✅ | `hooks.c` (`close_window`), `errors.c` |

---

## ❌ O QUE FALTA FAZER (OBRIGATÓRIO)

### 1. 🔴 **CRÍTICO — Makefile — Falta a regra `bonus`**

**Situação:** O Makefile não tem a regra `bonus` exigida pelo subject.

**Requisito (subject):**
> "Your Makefile must contain at least the rules `$(NAME)`, `all`, `clean`, `fclean` and `re`"
> "you must include a `bonus` rule in your Makefile, which will add all the various headers, libraries, or functions that are not allowed in the main part of the project. Bonuses must be placed in `_bonus.{c/h}` files"

**O que fazer:**
- [ ] Adicionar regra `bonus` ao Makefile
- [ ] Organizar código bónus em ficheiros `_bonus.c` / `_bonus.h` (opcional, pois código bónus está integrado)

**Prioridade:** 🟠 IMPORTANTE

---

### 2. 🔴 **CRÍTICO — README.md — Incompleto**

**Situação:** O README tem apenas 4 linhas genéricas.

**Requisitos (subject):**
- Primeira linha em itálico: *"This project has been created as part of the 42 curriculum by \<login1\>[, \<login2\>[, \<login3\>[...]]]*"
- Secção **"Description"** com objetivo e overview
- Secção **"Instructions"** com compilação/execução
- Secção **"Resources"** com referências + descrição de uso de AI

**O que fazer:**
- [ ] Escrever README.md conforme template do subject
- [ ] Adicionar primeira linha em itálico com login
- [ ] Detalhar raycasting e DDA no description
- [ ] Adicionar instruções de compilação (`make` e `./cub3D <map.cub>`)
- [ ] Listar recursos (raycasting tutorials, DDA, etc.)
- [ ] Documentar uso de AI (se aplicável)

**Prioridade:** 🟡 NECESSÁRIO

---

### 3. 🔴 **BUG CRÍTICO — Parsing — `read_file_lines()` perde linhas vazias**

**Situação:** O `ft_split(buffer, '\n')` **elimina linhas vazias**, o que viola o requisito do subject.

**Problema:**
```c
lines = ft_split(buffer, '\n');  // ❌ Perde linhas vazias
```

**Subject diz:**
> "Except for the map content, each type of element can be separated by one or more empty lines"
> "The map must be parsed as it looks in the file. Spaces are a valid part of the map"

**Cenário de erro:**
```
NO ./texture1.xpm

SO ./texture2.xpm

F 100,100,100
C 50,50,50

1111
1001
1N01
1111
```
As linhas vazias são **perdidas**, causando parsing incorreto.

**O que fazer:**
- [ ] Reescrever `read_file_lines()` para:
  - Usar `get_next_line()` (libft) ou leitura linha a linha
  - Preservar linhas vazias no array de linhas
  - Manter compatibilidade com `is_empty_line()` e lógica de parsing

**Alternativa rápida:**
```c
// Usar get_next_line() se existir em libft
// Ou implementar leitura linha a linha manualmente
```

**Ficheiro:** `src/parsing/parse_file.c`

**Prioridade:** 🔴 URGENTE

---

### 4. 🔴 **BUG CRÍTICO — Buffer fixo em `read_file_lines()`**

**Situação:** Buffer estático de 10000 bytes trunca ficheiros maiores.

```c
char	buffer[10000];
bytes_read = read(fd, buffer, 9999);  // ❌ Apenas 9999 bytes
```

**O que fazer:**
- [ ] Implementar leitura dinâmica (loop de `read()` ou `get_next_line`)
- [ ] Alocar memória dinamicamente para ficheiros grandes
- [ ] Concatenar blocos de dados até EOF

**Ficheiro:** `src/parsing/parse_file.c`

**Prioridade:** 🟠 IMPORTANTE

---

### 5. 🔴 **BUG — Validação de RGB com caracteres inválidos**

**Situação:** `ft_atoi` aceita strings inválidas como `"12abc"` silenciosamente.

```c
*r = ft_atoi(components[0]);  // ❌ "12abc" → 12 (sem erro)
```

**O que fazer:**
- [ ] Validar que cada componente RGB contém **apenas dígitos**
- [ ] Rejeitar strings com caracteres não-numéricos
- [ ] Exemplo: `"220,100abc,0"` deve dar erro

**Função:** `parse_rgb_values()` em `src/parsing/parse_colors.c`

**Prioridade:** 🟠 IMPORTANTE

---

### 6. 🔴 **BUG — Parsing — Falta validação de conteúdo após mapa**

**Situação:** O subject exige que o mapa seja o **último elemento**.

**Subject diz:**
> "Except for the map content which always has to be the last, each type of element can be set in any order in the file."

**Cenário de erro (deve falhar, mas não falha):**
```
NO ./texture1.xpm
SO ./texture2.xpm
WE ./texture3.xpm
EA ./texture4.xpm
F 100,100,100
C 50,50,50

1111
1001
1N01
1111

NO ./another_texture.xpm  <- ❌ Isto deveria ser rejeitado!
```

**O que fazer:**
- [ ] Após detectar primeira linha de mapa, validar que todas as linhas restantes são válidas do mapa
- [ ] Se houver linha de configuração (NO, SO, WE, EA, F, C) após mapa, retornar erro

**Ficheiro:** `src/parsing/parse_file.c` ou `parse_map.c`

**Prioridade:** 🟡 NECESSÁRIO

---

### 7. 🔴 **MEMORY LEAK — `free_scene_config` comentado**

**Situação:** Em `hooks.c`, a linha `free_scene_config(&data->config);` está **comentada**, causando leak das paths das texturas.

```c
int	close_window(t_data *data)
{
	// ...
	//free_scene_config(&data->config);  // ❌ Comentado = leak
	// ...
}
```

**O que fazer:**
- [ ] Descomentar `free_scene_config(&data->config);` em `close_window()`
- [ ] Testar com `valgrind` para confirmar leak resolvido

**Ficheiro:** `src/hooks.c` (linha ~29)

**Prioridade:** 🔴 URGENTE

---

### 8. 🔴 **ERROR HANDLING — Checks comentados em `init_mlx`**

**Situação:** Em `initialization.c`, checks de erro estão **comentados**, causando segfault se MLX falhar.

```c
void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	//if (!data->mlx)  // ❌ Comentado
	//	exit_error("mlx_init failed");
	
	data->win = mlx_new_window(...);
	//if (!data->win)  // ❌ Comentado
	//	exit_error("mlx_new_window failed");
}
```

**O que fazer:**
- [ ] Descomentar checks `if (!data->mlx)` e `if (!data->win)`
- [ ] Usar `error_exit()` em vez de `exit_error()`
- [ ] Testar simulando falha de MLX

**Ficheiro:** `src/initialization.c` (linhas ~19-23)

**Prioridade:** 🔴 URGENTE

---

## ⚠️ ERROS DE NORMINETTE (CRÍTICOS — 0 na avaliação!)

**SITUAÇÃO:** O projeto tem **centenas de erros de norminette** que resultam em **0 automático**.

### Erros por ficheiro:

#### `validate_map.c` — **92 erros**
- ❌ Espaços em vez de tabs (linhas 37-104)
- ❌ Linhas muito longas (>80 cols)
- ❌ Demasiadas funções (>5 no ficheiro)
- ❌ Funções com >25 linhas (`is_map_closed`)
- ❌ Newlines consecutivas

**O que fazer:**
- [ ] Dividir em 2 ficheiros: `validate_map.c` + `validate_map_utils.c`
- [ ] Converter **todos** os espaços em tabs
- [ ] Refatorar `is_map_closed()` para funções auxiliares menores
- [ ] Remover newlines consecutivas

#### `hooks.c` — **13 erros**
- ❌ Demasiadas funções (>5: `free_map`, `close_window`, `is_walkable`, `move_player`, `handle_movement`, `rotate_view`, `handle_rotation`, `toggle_mouse`, `key_hook`, `mouse_move`)
- ❌ Newlines consecutivas (linha 32)
- ❌ Comentário em scope inválido (linha 39)
- ❌ Linhas vazias dentro de funções

**O que fazer:**
- [ ] Mover funções auxiliares para novo ficheiro: `movement.c` ou `player_actions.c`
- [ ] Deixar em `hooks.c` apenas: `key_hook`, `mouse_move`, `close_window`, `free_map`
- [ ] Remover linhas vazias dentro de funções
- [ ] Comentários acima/abaixo de funções, não dentro

#### `render.c` — **11 erros**
- ❌ Função `render_3d_view()` com >25 linhas
- ❌ Função `render_wall_pixel()` com >4 argumentos
- ❌ Demasiadas funções (>5)
- ❌ Demasiadas variáveis em `render_3d_view()`
- ❌ Linhas vazias em funções
- ❌ Indentação errada (linhas 32-37)

**O que fazer:**
- [ ] Dividir `render_3d_view()` em funções menores (ex: `render_vertical_stripe()`)
- [ ] Refatorar `render_wall_pixel()` para receber struct em vez de 5 args
- [ ] Mover minimap para `src/raycast/draw_minimap.c` (já existe, mover logicamente)
- [ ] Deixar em `render.c` apenas funções públicas: `render`, `render_3d_view`

#### `cub3d.h` — **36 erros**
- ❌ **Nomes com maiúsculas:** `posX`, `posY`, `dirX`, `dirY`, `planeX`, `planeY` (FORBIDDEN_CHAR_NAME)
  - Devem ser: `pos_x`, `pos_y`, `dir_x`, `dir_y`, `plane_x`, `plane_y`
- ❌ Newlines consecutivas (linha 13)
- ❌ `#define` com expressões (FLAG_* — devem ser constantes simples)
- ❌ Struct com misalign de variáveis

**O que fazer:**
- [ ] **Renomear em `cub3d.h` E em TODO o projeto:**
  - `posX` → `pos_x` (usar multi_replace em todos os `.c`)
  - `posY` → `pos_y`
  - `dirX` → `dir_x`
  - `dirY` → `dir_y`
  - `planeX` → `plane_x`
  - `planeY` → `plane_y`
- [ ] Remover newline extra (linha 13)
- [ ] Alinhar struct (`t_img`, `t_scene_config`, `t_data`)

#### `initialization.c` — **14 erros**
- ❌ Comentários dentro de funções (linhas 19, 20, 31, 32, 43, 44, 88)
- ❌ Indentação errada: `data->screen.width = 800;` tem menos tabs
- ❌ Linhas vazias dentro de funções
- ❌ Espaços extras (linha 67)

**O que fazer:**
- [ ] Remover **todos** os comentários dentro de funções (mover para acima da função)
- [ ] Converter indentação para tabs apenas
- [ ] Remover linhas vazias dentro de funções

#### `draw.c` — **8 erros**
- ❌ Indentação errada (linha 62)
- ❌ Linhas longas (>80 cols)
- ❌ Comentário em scope (linha 88)

**O que fazer:**
- [ ] Corrigir indentação (tabs)
- [ ] Quebrar linha do `draw_line()` em 2 linhas
- [ ] Mover comentário da linha 88 para acima da função

#### `errors.c` — **1 erro**
- ❌ BRACE_SHOULD_EOL (linha 48): `}` seguido de outra coisa na mesma linha

```c
	cfg->ea_path = NULL;
}  // ← deve estar sozinha
```

**O que fazer:**
- [ ] Verificar linha 48 e garantir que `}` está em linha própria

#### `parse_colors.c` — **2 erros**
- ❌ Demasiadas funções (>5)
- ❌ BRACE_SHOULD_EOL

**O que fazer:**
- [ ] Mover `set_floor_color`, `set_ceiling_color`, `validate_rgb_value` para novo ficheiro ou inline

#### `parse_textures.c`, `parse_map.c`, `parse_utils.c`, `draw_minimap.c` — **5 erros**
- ❌ BRACE_SHOULD_EOL (chave `}` não em linha própria após `else if`)
- ❌ Comentário em scope

**O que fazer:**
- [ ] Garantir `}` em linha própria

#### `parse_file.c` — **2 erros**
- ❌ Indentação errada (linha 111): espaços em vez de tab
- ❌ `SPACE_REPLACE_TAB`

**O que fazer:**
- [ ] Corrigir indentação (tab)

#### `raycast.c` — **1 erro**
- ❌ Demasiadas funções (>5)

**O que fazer:**
- [ ] Agrupar funções relacionadas em bloco de comentário ou aceitar que é aceitável

#### `utils.c` — **1 erro**
- ❌ Linha vazia em função

**O que fazer:**
- [ ] Remover linha vazia

---

## 🏆 BÓNUS — Estado

| Bónus (subject) | Estado |
|---|---|
| Wall collisions | ✅ Implementado |
| Minimap system | ✅ Implementado |
| Doors (open/close) | ❌ Não implementado |
| Animated sprites | ❌ Não implementado |
| Mouse rotation | ✅ Implementado |

---

## 🔧 O QUE ESTÁ A MAIS (pode ser removido)

| Item | Notas | Ação |
|---|---|---|
| `struct_test.c` | Ficheiro de teste na raiz | [ ] Remover antes de submeter |
| `notas.md` | Notas pessoais | [ ] Remover antes de submeter |
| `en.norm.md` e `en.subject.md` | Documentos do subject | [ ] Remover antes de submeter |
| `CEILING_COLOR` e `FLOOR_COLOR` em header | Não usados (parsing já os lê) | [ ] Remover defines mortos |
| `WALL_NORTH_COLOR`, etc. | Debug colors não usadas | [ ] Remover defines mortos |
| `ft_read_line.c` em libft | Verificar se é usado | [ ] Remover se não usado |
| `draw_map` declarado no header | Declaração sem implementação | [ ] Remover prototipo |

---

## 📊 PLANO DE AÇÃO RECOMENDADO

### Fase 1: Corrigir erros críticos (bloqueadores)
1. ✅ Descomentar `free_scene_config()` em `close_window()` — **5 min**
2. ✅ Descomentar checks em `init_mlx()` — **5 min**
3. ✅ Renomear variáveis (`posX` → `pos_x`, etc.) em **TODO** o código — **30 min** (usar multi_replace)
4. ✅ Corrigir `read_file_lines()` para preservar linhas vazias — **20 min**
5. ✅ Validar RGB com chars numéricos — **10 min**
6. ✅ Validar que mapa é o último elemento — **10 min**

**Tempo total Fase 1:** ~80 minutos

### Fase 2: Corrigir norminette (obrigatório)
1. ✅ Refatorar `validate_map.c` (dividir + tabs + linhas) — **30 min**
2. ✅ Refatorar `hooks.c` (mover funções) — **20 min**
3. ✅ Refatorar `render.c` (dividir funções grandes) — **30 min**
4. ✅ Refatorar `cub3d.h` (alinhar struct) — **15 min**
5. ✅ Corrigir `initialization.c` (comentários + indentação) — **15 min**
6. ✅ Corrigir remaining erros menores (`draw.c`, `errors.c`, parsing, etc.) — **20 min**

**Tempo total Fase 2:** ~130 minutos

### Fase 3: Completar requisitos (obrigatório)
1. ✅ Adicionar regra `bonus` ao Makefile — **5 min**
2. ✅ Reescrever README.md completo — **20 min**

**Tempo total Fase 3:** ~25 minutos

### Fase 4: Limpeza final
1. ✅ Remover ficheiros extra (`struct_test.c`, `notas.md`, subjects) — **5 min**
2. ✅ Remover defines mortos — **5 min**
3. ✅ Testar compilação e norminette final — **10 min**

**Tempo total Fase 4:** ~20 minutos

---

**TEMPO TOTAL ESTIMADO:** ~255 minutos (~4 horas)

**Ordem de execução recomendada:** 1 → 2 → 3 → 4

Após todas as correções, o projeto deve:
- ✅ Compilar sem warnings
- ✅ Passar 100% da norminette
- ✅ Cumprir todos os requisitos obrigatórios
- ✅ Ter 3 bónus implementados (collisions, minimap, mouse)
