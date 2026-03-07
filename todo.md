# cub3D — Correções a Fazer

## 1. 🔴 `my_mlx_pixel_put` sem bounds checking
- **Ficheiro:** `src/utils.c`
- **Problema:** A função escreve diretamente no buffer sem verificar se `x` e `y` estão dentro dos limites da imagem. No `render_3d_view()` é chamada diretamente para ceiling, walls e floor — se algum cálculo der coordenadas fora do ecrã, há buffer overflow / segfault.
- **Correção:** Adicionar bounds check na função (ou criar versão safe usada no render loop).
- [x] Corrigido

## 2. 🟡 Memory leak no path de erro do parsing
- **Ficheiro:** `src/main.c` (linhas 28-29)
- **Problema:** Se `parse_scene_file` falha **depois** de alocar `data->map` (ex: na validação do mapa), o `main` faz `return(1)` sem libertar a config nem o mapa.
- **Correção:** Adicionar cleanup (`free_scene_config` + `free_map`) antes do `return(1)`, ou chamar `error_exit`.
- [x] Corrigido

## 3. 🟡 `error_exit` não liberta texturas nem MLX
- **Ficheiro:** `src/errors.c`
- **Problema:** `error_exit()` liberta config e mapa, mas não liberta texturas MLX, screen image, window, nem display. Se chamada depois de `load_all_textures()`, haverá leaks.
- **Correção:** Unificar lógica com `close_window()` ou adicionar cleanup completo a `error_exit`.
- [ ] Corrigido
