# Relatório de Análise do Projeto `cub3D`

Data: 2026-03-07
Repositório: `Cub3d` (branch `TiBranch`)

## 1) Âmbito e metodologia

Este relatório analisa o projeto presente no workspace, com foco em:
- arquitetura e organização de módulos;
- conformidade com o subject do `cub3D`;
- robustez de parsing/validação/render;
- qualidade de build e conformidade com Norm;
- riscos técnicos e plano de mitigação.

### Fontes analisadas
- `Makefile`, `README.md`, `inc/cub3d.h`
- Código em `src/` (incluindo `src/parsing/` e `src/raycast/`)
- Documentação local: `en.subject.md`, `en.norm.md`, `todo.md`
- Estrutura geral: `libft/`, `minilibx-linux/`, `maps/`, `textures/`

### Verificações executadas
- Build: `make` ✅ (compilação concluída com sucesso)
- Norm: `norminette inc src` ❌ (múltiplos erros)

> Nota: não foi feita validação de execução gráfica interativa neste relatório (dependência de ambiente X11/janela).

---

## 2) Visão geral da arquitetura

### Estrutura de alto nível
- `src/main.c`: ciclo de vida principal (parse → init MLX → carregar texturas → loop).
- `src/initialization.c`: inicialização de janela, framebuffer, cache de raios, hooks.
- `src/render.c`: pipeline de render por frame (3D + minimap + jogador + rays debug).
- `src/hooks.c`: input (WASD, setas, mouse, toggles), movimento/rotação, cleanup.
- `src/parsing/`: parser de `.cub` (texturas, cores, mapa, utilitários).
- `src/raycast/`: DDA, cálculo de hit/distância e desenho de raios no minimapa.
- `src/validate_map.c`: validação de caracteres, jogador único e encerramento do mapa.

### Qualidade de separação modular
Ponto forte: o projeto está funcionalmente dividido por responsabilidades claras (parsing, motor de raycast, desenho, input e erros), o que facilita manutenção e defesa técnica.

---

## 3) Conformidade com o subject (mandatório)

### Requisitos essenciais observados
- Input `.cub` e parser dedicado: **implementado**.
- Texturas por orientação de parede (N/S/E/W): **implementado** (`wall_side` + `tex[4]`).
- Cores de teto/chão por parsing RGB: **implementado**.
- Teclas obrigatórias (WASD, setas, ESC, fechar janela): **implementado**.
- Uso de MiniLibX: **implementado**.

### Itens de atenção de entrega
- `Makefile`: regras `all`, `clean`, `fclean`, `re` presentes.
- Regra `bonus`: **não encontrada** (o subject/documentação local indica exigência).
- `README.md`: muito curto, não cobre documentação mínima esperada para avaliação.

---

## 4) Avaliação técnica por subsistema

### 4.1 Parsing e validação de ficheiro
**Pontos positivos**
- Validação de extensão `.cub` (`validate_file_extension`).
- Leitura dinâmica de linhas com crescimento de buffer (`read_file_lines`).
- Controle de duplicação de chaves de configuração via bitmask (`config_flags`).
- Parsing robusto de RGB com trim e validação de intervalo [0..255].

**Riscos/limitações**
- `validate_texture_path` apenas confirma extensão e abertura do caminho; não valida formato XPM além do load posterior.
- Em `parse_scene_file`, quando `extract_and_validate_map` falha, o mapa eventualmente alocado em `data->map` pode ficar para cleanup posterior (não é crash, mas exige disciplina de ciclo de vida).

### 4.2 Validação de mapa
**Pontos positivos**
- Verificação de caracteres válidos.
- Exigência de exatamente um jogador inicial.
- Teste de fechamento de mapa com tratamento de bordas e espaços.

**Riscos/limitações**
- A lógica de fechamento usa comprimento variável de linhas (`ft_strlen`) em tempo real; funciona, mas é sensível a mapas irregulares e difícil de evoluir.
- Não há normalização/padding do mapa para matriz retangular, o que simplificaria várias verificações.

### 4.3 Raycasting e render
**Pontos positivos**
- Implementação DDA clássica com `delta_dist`, `side_dist`, `step` e cálculo de distância perpendicular.
- Correção visual básica de distâncias (`perp_wall_dist` mínimo).
- Seleção de textura por face atingida (`WALL_NORTH/SOUTH/WEST/EAST`).
- Minimap com raios opcional e cache de raios por coluna.

**Riscos/limitações**
- Render e debug no mesmo frame podem custar performance em máquinas lentas (raios no minimapa para todas colunas quando ativo).
- Algumas funções concentram muitas responsabilidades (e excedem limites da Norm), dificultando manutenção incremental.

### 4.4 Input, movimento e ciclo de vida
**Pontos positivos**
- Movimento separado por eixo reduz clipping em cantos (`is_walkable` por eixo).
- Rotação de direção e plano de câmara consistente.
- Cleanup centralizado com destruição de texturas, imagem, janela, display e buffers.

**Riscos/limitações**
- Hook de mouse e recenter contínuo pode variar entre ambientes X11; convém validar comportamento em diferentes setups.
- `is_walkable` trata `space` como atravessável (porque só bloqueia `'1'`); isto pode ser desejado/indesejado dependendo da política de mapa e do validador.

---

## 5) Estado de qualidade e conformidade Norm

A execução de `norminette inc src` retorna muitos erros, incluindo:
- `MIXED_SPACE_TAB`, `TOO_FEW_TAB`, `CONSECUTIVE_SPC`
- `TOO_MANY_LINES`, `TOO_MANY_FUNCS`, `TOO_MANY_VARS_FUNC`, `TOO_MANY_ARGS`
- `LINE_TOO_LONG`, `EMPTY_LINE_FUNCTION`
- problemas de alinhamento em declarações/protótipos

Ficheiros mais impactados pelo output observado:
- `inc/cub3d.h`
- `src/hooks.c`
- `src/render.c`
- `src/initialization.c`
- `src/main.c`
- `src/draw.c`
- `src/errors.c`

**Conclusão de qualidade formal:** atualmente há risco alto de reprovação por Norm, mesmo com build funcional.

---

## 6) Riscos priorizados

### Prioridade Alta (bloqueadores de avaliação)
1. **Conformidade Norm** em múltiplos ficheiros centrais.
2. **`Makefile` sem target `bonus`** (conforme documentação local/subject).
3. **`README.md` insuficiente** para contexto de defesa e requisitos de entrega.

### Prioridade Média
4. Funções grandes e com múltiplas responsabilidades (especialmente em `render.c` e `hooks.c`).
5. Complexidade da validação de mapa irregular sem normalização matricial.
6. Custo de debug visual (rays no minimapa em todas as colunas) quando ativado.

### Prioridade Baixa
7. Comentários e consistência de estilo misturam português/inglês.
8. Possível código de debug/artefactos não essenciais em entrega final.

---

## 7) Plano de ação recomendado (prático)

### Fase 1 — Desbloquear avaliação
- Refatorar `inc/cub3d.h` para cumprir Norm (alinhamentos, macros, nomes e largura de linha).
- Partir `render.c` e `hooks.c` em unidades menores (`render_core.c`, `render_minimap.c`, etc.).
- Ajustar funções >25 linhas e >5 variáveis, e assinaturas >4 argumentos.
- Adicionar target `bonus` no `Makefile` (mesmo que inicialmente delegue para `all`/ficheiros `_bonus`).

### Fase 2 — Robustez
- Introduzir normalização do mapa (padding com espaços) numa cópia interna para simplificar fecho e colisão.
- Tornar política de walkable explícita para `' '` (bloquear no movimento se fizer sentido para o teu desenho de mapa).
- Melhorar mensagens de erro para contexto de defesa.

### Fase 3 — Entrega/defesa
- Expandir `README.md`: descrição, build/run, controlos, formato `.cub`, limitações conhecidas, testes usados.
- Preparar conjunto mínimo de mapas de regressão (válido + inválidos típicos).

---

## 8) Parecer final

O projeto está **funcionalmente bem estruturado e com motor base de raycasting implementado**.

O principal risco atual não é a ausência de features mandatorias, mas sim **conformidade formal (Norm + empacotamento de entrega)**. Com foco nas correções de Norm e acabamento de entrega (`Makefile`/`README`), o projeto tem boa base para avaliação sólida.
