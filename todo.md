# TODO do Projeto `cub3D`

Data: 2026-03-07

## ✅ Feito

- [x] Estrutura base do projeto organizada (`src/`, `inc/`, `libft/`, `minilibx-linux/`, `maps/`).
- [x] Pipeline principal implementado: parse de `.cub` → init MLX → render loop.
- [x] Raycasting funcional com DDA e texturas por orientação (N/S/W/E).
- [x] Cores de chão e teto por parsing RGB.
- [x] Controlos principais implementados (`W`, `A`, `S`, `D`, setas, `ESC`, fechar janela).
- [x] Minimap e opção de mostrar/ocultar raios (`R`).
- [x] Build funcional com `make` (estado atual: compila).
- [x] Limpeza de código morto recente:
  - [x] Removido `struct_test.c`.
  - [x] Removidas funções/protótipos órfãos (`draw_ray_debug`, `init_ray_direction`, `draw_square`, `draw_map`, etc.).
- [x] Relatório técnico criado em `relat.md`.

## ⚠️ Falta fazer (prioridade alta)

- [ ] Corrigir **Norminette** (bloqueador principal neste momento).
  - [ ] `inc/cub3d.h`: muitos erros de formatação, nomes e alinhamento.
  - [ ] `src/hooks.c`: funções a mais no ficheiro, funções longas e estilo.
  - [ ] `src/render.c`: excesso de linhas/variáveis/args e indentação.
  - [ ] `src/main.c`, `src/initialization.c`, `src/draw.c`, `src/errors.c`.
- [ ] Adicionar regra `bonus` no `Makefile` (exigência do subject).
- [ ] Melhorar `README.md` (atualmente muito curto para entrega/defesa).

## 🛠️ Falta fazer (prioridade média)

- [ ] Refatorar ficheiros grandes para cumprir Norm sem perder clareza:
  - [ ] dividir `render.c` em unidades menores;
  - [ ] dividir `hooks.c` por responsabilidade.
- [ ] Rever consistência de estilo (português/inglês em comentários e mensagens).
- [ ] Afinar mensagens de erro para facilitar defesa.

## 🧪 Falta fazer (validação final)

- [ ] Correr `norminette inc src` até ficar sem erros.
- [ ] Correr `make re` e validar execução com mapas de teste.
- [ ] Correr `val`/Valgrind e registar estado de memória.

## 📌 Nota rápida

Neste momento, o projeto está **funcional**, mas o risco de avaliação está concentrado em **conformidade Norm + acabamento de entrega** (`Makefile`/`README`).
