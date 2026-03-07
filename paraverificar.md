# cub3D - Relatório de Progresso & TODO

## 📊 Estado Geral do Projeto

O projeto está **bastante avançado** na parte obrigatória. O core do jogo funciona: parsing do ficheiro `.cub`, raycasting com texturas, minimapa, movimentação e rotação. Faltam correcções de Norma, pequenas melhorias de robustez e o README obrigatório.

---

## ✅ O QUE ESTÁ FEITO

### 1. Parsing do ficheiro `.cub`
- [x] Validação da extensão `.cub`
- [x] Leitura completa do ficheiro com `get_next_line`
- [x] Parsing das texturas (NO, SO, WE, EA) com validação `.xpm`
- [x] Parsing das cores (F, C) com validação RGB [0,255]
- [x] Detecção de elementos duplicados (texturas e cores)
- [x] Verificação de que todos os 6 elementos estão presentes (bitmask `FLAG_ALL`)
- [x] Extração do mapa a partir das linhas do ficheiro
- [x] Validação de que o mapa é o último elemento
- [x] Rejeição de conteúdo de configuração após o mapa
- [x] Separação config/mapa feita corretamente

### 2. Validação do Mapa
- [x] Validação de caracteres válidos (`0`, `1`, `N`, `S`, `E`, `W`, espaço)
- [x] Contagem de posições de jogador (exatamente 1)
- [x] Verificação de mapa fechado por paredes (`is_map_closed`)
- [x] Espaços tratados como exterior (não podem tocar `0` ou jogador)
- [x] Cálculo das dimensões do mapa (largura e altura)

### 3. Raycasting (DDA)
- [x] Implementação completa do algoritmo DDA
- [x] Inicialização de `delta_dist`, `step`, `side_dist`
- [x] Loop DDA com detecção de colisão com paredes
- [x] Cálculo de distância perpendicular (correcção fish-eye)
- [x] Determinação do lado da parede (NORTH, SOUTH, EAST, WEST)
- [x] Cálculo do ponto exato de impacto (`hit_x`, `hit_y`)

### 4. Renderização 3D
- [x] Texturas nas paredes (4 texturas diferentes conforme direcção)
- [x] Carregamento de texturas `.xpm` via miniLibX
- [x] Cálculo correto de `tex_x` e `tex_y`
- [x] Sombreamento no lado horizontal das paredes (`side == 1`)
- [x] Cores de teto e chão lidos do ficheiro `.cub`
- [x] Framebuffer com `mlx_new_image` + `mlx_get_data_addr`

### 5. Movimentação do Jogador
- [x] Teclas W/A/S/D para mover (frente, esquerda, trás, direita)
- [x] Setas esquerda/direita para rodar a vista
- [x] Colisão com paredes implementada (`is_walkable`)
- [x] Rotação do vetor de direcção e plano de câmara (`rotate_view`)
- [x] Velocidade de movimento e rotação configuráveis

### 6. Controlo de Janela
- [x] Tecla ESC fecha a janela e sai corretamente
- [x] Clicar no X vermelho fecha a janela (hook evento 17)
- [x] Limpeza de recursos no fecho (texturas, imagens, display, mapa, config)

### 7. Minimapa (Bónus)
- [x] Desenho do mapa com paredes no canto superior esquerdo
- [x] Posição do jogador como círculo vermelho
- [x] Raios visíveis no minimapa (toggle com tecla R)

### 8. Rato (Bónus)
- [x] Rotação da vista com o rato
- [x] Toggle rato com tecla M
- [x] Sensibilidade configurável
- [x] Warp do cursor para o centro do ecrã

### 9. Infraestrutura
- [x] Makefile com regras `all`, `clean`, `fclean`, `re`
- [x] Compilação com `-Wall -Wextra -Werror`
- [x] Utilização da libft própria
- [x] Ficheiros de mapa de teste (`maptest.cub`, `maptest2.cub`, `maptest3.cub`)
- [x] Múltiplas texturas disponíveis em `textures/`
- [x] Regra `val` para Valgrind com suppressions

---

## ❌ O QUE FALTA FAZER

### 🔴 CRÍTICO (Obrigatório para a avaliação)

#### Makefile
- [ ] **Regra `bonus` em falta no Makefile** — O subject exige explicitamente a regra `bonus`. Mesmo que os bónus estejam no código principal, a regra precisa de existir.

#### README.md
- [ ] **README.md não cumpre os requisitos do subject** — O README atual é muito básico. Segundo o subject, deve conter:
  - [ ] Primeira linha em itálico: *This project has been created as part of the 42 curriculum by \<login1\>, \<login2\>*
  - [ ] Secção **"Description"** com objetivo e resumo do projeto
  - [ ] Secção **"Instructions"** com compilação, instalação e execução
  - [ ] Secção **"Resources"** com referências e descrição do uso de AI
  - [ ] Escrito em inglês

### 🟡 NORMA (Erros que dão 0 na avaliação)

#### Comentários `//` dentro de funções e ficheiros `.c`
- [ ] **`validate_map.c`** — Comentários com `//` em todo o ficheiro (linhas 17-18, 25-26, 33-34, 58-59, 74-76, 108-112). A Norma proíbe `//` — só permite `/* */`.
- [ ] **`render.c`** — Comentários com `//` em todo o ficheiro (linhas 15, 47, 61, 72, 91, etc.)
- [ ] **`parse_file.c`** — Comentários com `//` (linhas 17, 30, etc.)
- [ ] **`parse_textures.c`** — Comentários com `//`
- [ ] **`parse_colors.c`** — Comentários com `//`
- [ ] **`parse_map.c`** — Comentários com `//`
- [ ] **`parse_utils.c`** — Comentários com `//`
- [ ] **`initialization.c`** — Comentários com `//` (linha 92-93)
- [ ] **`draw_minimap.c`** — Comentário com `//` (linha 27)
- [ ] **`raycast.c`** — Comentários em português com `//`
- [ ] **`init_dda.c`** — Comentários em português com `//` e `/* */` multilinhas dentro de funções

#### Funções por ficheiro (máx. 5)
- [ ] **`hooks.c`** tem **10 funções** — máximo permitido é 5. Precisa de ser dividido em pelo menos 2 ficheiros.
- [ ] **`render.c`** tem **8 funções** — precisa de ser dividido em pelo menos 2 ficheiros.
- [ ] **`validate_map.c`** tem **6 funções** — precisa de perder 1 ou dividir.
- [ ] **`parse_file.c`** tem **7 funções** — precisa de ser dividido.
- [ ] **`parse_colors.c`** tem **6 funções** — precisa de perder 1 ou dividir.
- [ ] **`raycast.c`** tem **6 funções** — precisa de perder 1 ou dividir.

#### Parâmetros de função (máx. 4)
- [ ] **`render_wall_pixel()`** em `render.c` tem **5 parâmetros** — máximo é 4. Precisa de refactor (usar struct ou reorganizar).

#### Linhas por função (máx. 25)
- [ ] **`render_3d_view()`** em `render.c` — tem ~50 linhas. Precisa de ser dividida em sub-funções.
- [ ] **`read_file_lines()`** em `parse_file.c` — tem ~30 linhas. Ligeiramente acima do limite.

#### Variáveis por função (máx. 5)
- [ ] **`render_3d_view()`** em `render.c` — declara 8 variáveis (`x`, `camera_x`, `ray`, `line_height`, `draw_start`, `draw_end`, `y`, `color`). Máximo é 5.

#### `#define` sem `# ` (Norma 42)
- [ ] Em `cub3d.h`, os `#define` de `MINIMAP_SCALE`, `MINIMAP_OFFSET_X`, `MINIMAP_OFFSET_Y` (linhas 64-66) não têm espaço após `#` (`#define` em vez de `# define`). Na Norma 42 dentro de `#ifndef`/`#endif`, os defines devem ter indentação `# define`.

#### Indentação nas structs do header
- [ ] Verificar se `t_img`, `t_data` e outras structs com `{` na mesma linha estão conforme a Norma (braces na linha seguinte).

#### Comentários em português
- [ ] A Norma exige que **todos os comentários sejam em inglês**. Existem comentários em português em `init_dda.c`, `raycast.c`, `initialization.c`, `cub3d.h`, etc.

### 🟠 ROBUSTEZ / EDGE CASES

#### Parsing
- [ ] **Espaços antes de vírgulas nas cores** — O parsing de `F 0, 255, 255` pode falhar porque `ft_split(',')` irá criar componentes com espaços (ex: `" 255"`), e `is_valid_rgb_string` rejeita espaços. O subject mostra `0, 255, 255` como exemplo válido. Adicionar trim/skip de espaços nos componentes RGB.
- [ ] **Tabs no identificador de textura** — `parse_texture_line` verifica `"NO "` (com espaço). Linha como `"NO\t./path"` seria ignorada. Considerar suportar tab como separador.
- [ ] **Linhas vazias dentro do mapa** — `count_map_lines` para de contar quando encontra uma linha não-mapa. Uma linha vazia no meio do mapa cortaria o mapa em dois. O subject diz que linhas vazias podem separar elementos *exceto* dentro do mapa. Verificar se linhas vazias no meio do mapa geram erro.
- [ ] **Map sem newline final** — Verificar se o último mapa sem `\n` final é corretamente processado pelo `get_next_line`.

#### Gestão de memória
- [ ] **`error_exit()` não liberta texturas MLX** — A função `error_exit` só liberta `config` e `map`, mas não destrói imagens MLX nem a janela/display. Se `load_all_textures` falhar a meio (ex: textura 3 falha), as texturas 0-2 ficam em leak.
- [ ] **`parse_scene_file` falha sem limpar `data->config`** — Se `parse_configuration` falha, a config alocada (paths) pode ficar por libertar dependendo do ponto de falha.

#### Validação do mapa
- [ ] **Mapa com linhas de comprimento irregular + espaços** — O `is_map_closed` verifica `ft_strlen(map[i-1]) <= j`, mas linhas mais curtas podem causar falsos positivos. Verificar se `map[i-1][j]` acede além do limite da string quando `j >= strlen(map[i-1])`.

### 🔵 BÓNUS (Opcionais, avaliados só com parte obrigatória perfeita)

- [x] ~~Colisão com paredes~~ ✅ (já implementado em `is_walkable`)
- [x] ~~Minimapa~~ ✅ (já implementado)
- [ ] **Portas que abrem e fecham** — Não implementado
- [ ] **Sprites animados** — Não implementado
- [x] ~~Rotação da vista com o rato~~ ✅ (já implementado)

### 🔵 MELHORIAS SUGERIDAS (Não obrigatórias)

- [ ] Resolução da janela configurável (atualmente hardcoded 800x600)
- [ ] Mensagens de erro mais consistentes (algumas têm "WTF!", "Blahhhh!!", etc.)
- [ ] O mouse esconde-se automaticamente ao iniciar (`init_hooks` chama `mlx_mouse_hide`) sem o toggle estar ativo — pode confundir
- [ ] `draw_map()` declarada no header mas é a função `draw_minimap` em `render.c` — nome inconsistente
- [ ] Struct `s_data` tem campos comentados em português (`// relativo ao mapa`, etc.)
- [ ] `struct_test.c` na raiz parece ser ficheiro de teste — remover antes de entregar
- [ ] Ficheiro `notas.md` na raiz — remover antes de entregar

---

## 📁 Resumo por Ficheiro

| Ficheiro | Funções | Estado Norma | Notas |
|---|---|---|---|
| `main.c` | 1 | ✅ OK | — |
| `hooks.c` | 10 | ❌ >5 funções | Dividir em 2+ ficheiros |
| `render.c` | 8 | ❌ >5 funções, >25 linhas, >5 vars | Dividir e refactorar |
| `draw.c` | 4 | ✅ OK | — |
| `utils.c` | 4 | ✅ OK | — |
| `errors.c` | 3 | ✅ OK | — |
| `initialization.c` | 5 | ✅ OK | Comentários `//` |
| `validate_map.c` | 6 | ❌ >5 funções, comentários `//` | Dividir/mover 1 função |
| `parse_file.c` | 7 | ❌ >5 funções, >25 linhas | Dividir |
| `parse_textures.c` | 5 | ✅ OK | Comentários `//` |
| `parse_colors.c` | 6 | ❌ >5 funções | Dividir/mover 1 função |
| `parse_map.c` | 5 | ✅ OK | Comentários `//` |
| `parse_utils.c` | 4 | ✅ OK | — |
| `raycast/raycast.c` | 6 | ❌ >5 funções | Dividir/mover 1 função |
| `raycast/init_dda.c` | 4 | ✅ OK | Comentários `//` e PT |
| `raycast/draw_minimap.c` | 2 | ✅ OK | Comentário `//` |

---

## 🎯 Prioridades de Acção

1. **Corrigir TODOS os comentários `//`** → Converter para `/* */` ou remover
2. **Traduzir comentários em PT para EN**
3. **Dividir ficheiros com >5 funções** (`hooks.c`, `render.c`, `parse_file.c`, etc.)
4. **Refactorar `render_3d_view()`** — demasiadas linhas e variáveis
5. **Refactorar `render_wall_pixel()`** — demasiados parâmetros
6. **Adicionar regra `bonus` ao Makefile**
7. **Reescrever o README.md** conforme os requisitos do subject
8. **Corrigir parsing de cores com espaços** (edge case do subject)
9. **Melhorar `error_exit()`** para libertar recursos MLX
10. **Remover ficheiros de teste** (`struct_test.c`, `notas.md`) antes da entrega
