# Auditoria do projeto `cub3D` (07/03/2026)

## Estado geral

- O projeto compila com sucesso (`make`).
- A arquitetura está bem separada por módulos (`parsing`, `raycast`, `render`, `hooks`).
- Há funcionalidades de bónus implementadas (minimap, rotação por rato).

## Pontos críticos (prioridade alta)

1. **Norminette com muitos erros**
   - `inc/cub3d.h`
   - `src/validate_map.c`
   - `src/hooks.c`
   - `src/initialization.c`
   - `src/draw.c`
   - `src/errors.c`
   - `src/utils.c`

   Tipos de erro encontrados:
   - mistura de tabs/espaços
   - alinhamento de declarações/funções
   - linhas demasiado longas
   - linhas vazias indevidas
   - `TOO_MANY_FUNCS` no mesmo ficheiro

2. **`README.md` incompleto face ao subject**
   Faltam itens obrigatórios:
   - primeira linha em itálico com os logins
   - secção **Description**
   - secção **Instructions**
   - secção **Resources** (incluindo como AI foi usada)

3. **`Makefile` sem regra `bonus`**
   - O subject pede explicitamente: `all`, `clean`, `fclean`, `re`, `bonus`.

4. **Código morto / incoerência de fluxo de debug**
   - `draw_ray_debug` está definido e declarado mas sem utilização efetiva.

5. **Risco em caminho de erro (exit code)**
   - `error_exit()` chama `close_window()`, e `close_window()` faz `exit(0)`.
   - Em cenário de erro, o esperado é terminar com código não-zero.

## Pontos médios (melhorias recomendadas)

- Possível custo extra por cálculo de raios para 3D e minimap no mesmo frame.
- Mensagens de erro ainda podem ser mais específicas para facilitar defesa.
- Pequenas oportunidades de robustez no parsing (checks de alocação em alguns caminhos).

## Verificações feitas

- Build principal: `make` ✅
- Build `libft`: `make -C libft` ✅
- Norm: `norminette inc src` ❌ (muitos erros)
- Parsing (exemplo inválido):
  - `./cub3D maps/maptest.txt` → `Error` + extensão inválida, `EXIT:1` ✅
  - `./cub3D maps/test_1_player_touches_space.cub` → `Error Invalid map structure`, `EXIT:1` ✅

## Parecer final

O projeto está **funcionalmente bem encaminhado**, mas para avaliação final de 42 o maior risco neste momento é:

1. **Norminette**
2. **README obrigatório do subject**
3. **`bonus` no Makefile**

A lógica principal do raycasting está utilizável; o bloqueador de nota agora é mais de conformidade/entrega do que de arquitetura base.

## Plano curto recomendado (ordem)

1. Limpar `norminette` por prioridade (`inc/cub3d.h`, `validate_map.c`, `hooks.c`).
2. Atualizar `README.md` para cumprir 100% o subject.
3. Adicionar regra `bonus` no `Makefile`.
4. Remover/alinhar código de debug não usado.
5. Ajustar `error_exit`/`close_window` para exit code correto em erro.
