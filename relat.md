# Relatório de Auditoria — cub3D

Data: 2026-03-07  
Projeto auditado: `Cub3d`  
Critérios usados: `cub3D correction.html` + `en.subject.md`

## 1) Metodologia

Foi feita validação em 4 frentes:
- **Build/Makefile** (`make`, `make -q`, regras obrigatórias)
- **Norminette** (pastas `inc` e `src`)
- **Comportamento em execução** (smoke-tests com `timeout`, argumentos, parsing de `.cub`)
- **Gestão de erros/memória** (mensagens de erro + `valgrind` em caminhos de erro)

> Nota: testes de interação gráfica fina (minimizar/restaurar janela, fluidez visual, validação visual de texturas) não são totalmente automatizáveis aqui. Nesses pontos foi usada combinação de leitura de código + smoke-tests.

---

## 2) Resultado por critério de avaliação (folha de correção)

### 2.1 Executable name
- **Estado: ✅ PASS**
- Evidência:
  - `make -s` gera executável `cub3D`
  - `ls -l cub3D` confirma nome correto

### 2.2 Configuration file (`NO`, `SO`, `WE`, `EA`, `F`, `C`, mapa, erros)
- **Estado: ✅ PASS (com evidência forte)**
- Evidência prática:
  - Extensão inválida (`.txt`) → `Error` + `File must have .cub extension`
  - Ficheiro inexistente → `Error` + `Cannot open file`
  - Chave desconhecida (`ZZ`) → `Error` + `Invalid configuration line`
  - Chave duplicada (`NO` repetido) → `Error` + `Duplicate texture definition`
  - Path de textura inválido → `Error` + `Cannot open texture file`
  - Mapa inválido (`maps/test_1_player_touches_space.cub`) → `Error` + `Invalid map structure`
- Evidência de código:
  - `src/parsing/parse_file.c`, `parse_textures.c`, `parse_colors.c`, `parse_map.c`, `src/validate_map.c`

### 2.3 Technical elements of display
- **Estado: 🟨 PARCIAL (smoke-test OK, verificação visual manual pendente)**
- Evidência:
  - `timeout 2 ./cub3D maps/maptest.cub` retorna `124` (loop gráfico ativo, processo em execução)
- Falta confirmar manualmente:
  - Janela abre corretamente em ambiente de defesa
  - Conteúdo mantém consistência ao minimizar/maximizar/ocultar

### 2.4 User basic events
- **Estado: 🟨 PARCIAL (código OK, validação manual pendente)**
- Evidência de código:
  - Cruz vermelha: `mlx_hook(..., 17, ..., close_window, ...)` em `src/initialization2.c`
  - ESC: `KEY_ESC` em `key_hook` (`src/hooks.c`)
  - Teclas movimento: `W/A/S/D` em `handle_movement` (`src/hooks2.c`)

### 2.5 Movements
- **Estado: 🟨 PARCIAL (lógica OK, fluidez/experiência manual pendente)**
- Evidência de código:
  - Rotação setas: `KEY_LEFT` / `KEY_RIGHT` em `src/hooks3.c`
  - Movimento frontal/traseiro/lateral em `src/hooks2.c`
  - Orientação inicial `N/S/E/W`: `set_player_direction` em `src/utils.c`
- Evidência prática:
  - Smoke-tests para mapas mínimos com `N/S/E/W` → processo entra em loop (exit `124` com timeout)
- Falta confirmar manualmente:
  - Fluidez visual durante movimentação

### 2.6 Walls
- **Estado: 🟨 PARCIAL (implementação presente, validação visual manual pendente)**
- Evidência de código:
  - Texturas por lado da parede: `ray->wall_side` + `data->tex[ray->wall_side]`
  - Render com textura: `src/render_texture.c`, `src/render_3d.c`, `src/raycast/raycast*.c`
  - Cores de chão/teto vindas de config: `data->config.floor_color`, `data->config.ceiling_color`
  - Path inválido de textura gera erro (testado)
- Falta confirmar manualmente:
  - Correção visual de orientação N/S/E/W no render

### 2.7 Error management
- **Estado: ✅ PASS (com ressalva de testes manuais extra recomendados)**
- Evidência prática:
  - Sem args e args a mais: mensagem de uso e saída limpa (exit `1`)
  - Erros de parsing/config: mensagens explícitas + `Error\n`
  - Casos inválidos testados não causaram crash
- Evidência de código:
  - `error_return`, `error_exit` em `src/errors.c`

### 2.8 Leaks
- **Estado: ✅ PASS nos caminhos testados**
- Evidência:
  - `valgrind ./cub3D` (sem args) → `All heap blocks were freed`
  - `valgrind ./cub3D /tmp/cub_bad_tex_path.cub` → `All heap blocks were freed`
- Observação:
  - Leak-check completo de sessão gráfica longa deve ser repetido manualmente na defesa

---

## 3) Conformidade com `en.subject.md` (itens gerais)

### 3.1 Makefile obrigatório
- **`all`, `clean`, `fclean`, `re`**: ✅ presentes
- **`bonus`**: ❌ **ausente**
  - Evidência: `make -n bonus` → `No rule to make target 'bonus'`
  - Impacto: não conformidade com requisito explícito do subject

### 3.2 Sem relink desnecessário
- **Estado: ✅ PASS**
- Evidência: `make -q` retorna `0` após build (alvo atualizado)

### 3.3 Norminette
- **Estado: ❌ FAIL (global)**
- Resultado observado com `norminette inc src`:
  - Muitos erros em `inc/cub3d.h` (tabs/espaços mistos, alinhamento, comentários/formatos, macros)
  - Erros em parsing:
    - `src/parsing/parse_colors.c` (`TOO_MANY_LINES`, `TOO_MANY_FUNCS`, etc.)
    - `src/parsing/parse_file.c` (`TOO_MANY_VARS_FUNC`, `TOO_MANY_LINES`, `TOO_MANY_FUNCS`)
    - `src/parsing/parse_textures.c` (`BRACE_SHOULD_EOL`)
    - `src/parsing/parse_utils.c` (`BRACE_SHOULD_EOL`)
- Vários ficheiros de render/hooks/raycast já estão OK, mas o estado **global** ainda reprova.

### 3.4 README obrigatório
- **Estado: ❌ FAIL**
- `README.md` atual não cumpre requisitos mínimos do subject:
  - Falta primeira linha em itálico com formato pedido
  - Falta secções completas `Description`, `Instructions`, `Resources`
  - Conteúdo muito reduzido

---

## 4) Veredito atual (honesto para defesa)

Se a avaliação fosse hoje, o projeto está **funcional em partes importantes**, mas **ainda não está 100% de acordo com o que é necessário** por causa de:
1. **Norminette global a falhar**
2. **Regra `bonus` ausente no Makefile**
3. **README não conforme ao subject**
4. Alguns critérios gráficos dependem de **validação manual em ambiente de defesa**

---

## 5) Prioridades para fechar conformidade

1. **Corrigir `norminette`** em `inc/cub3d.h` e `src/parsing/*` com prioridade máxima.
2. **Adicionar target `bonus`** no `Makefile` (mesmo que redirecione para mandatory, conforme estratégia escolhida).
3. **Reescrever `README.md`** para cumprir exatamente o template exigido no subject.
4. Fazer checklist manual final:
   - minimizar/restaurar janela
   - ESC e cruz vermelha
   - W/A/S/D + setas
   - texturas N/S/E/W visualmente corretas
   - piso/teto ao alterar `.cub`
   - valgrind em execução real (abrir/fechar janela)

---

## 6) Comandos usados (resumo)

```bash
make -s
make -q
make -n bonus
norminette inc src
./cub3D
./cub3D maps/maptest.txt
./cub3D maps/does_not_exist.cub
./cub3D /tmp/cub_unknown_key.cub
./cub3D /tmp/cub_duplicate_key.cub
./cub3D /tmp/cub_bad_tex_path.cub
./cub3D maps/test_1_player_touches_space.cub
timeout 2 ./cub3D maps/maptest.cub
valgrind --leak-check=full --show-leak-kinds=all ./cub3D
valgrind --leak-check=full --show-leak-kinds=all ./cub3D /tmp/cub_bad_tex_path.cub
```

---

## 7) Conclusão curta

- **Mandatory funcional**: em boa evolução.  
- **Mandatory formal (subject/defesa)**: **ainda não fechado** (norminette + make bonus + README).  
- Após corrigir esses 3 pontos, o projeto fica muito mais seguro para avaliação.
