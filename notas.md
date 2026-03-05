**errors.c**
	serve para centralizar os erros e limpeza de memória.
		limpa o mapa - free_map
		limpa a configuração - free_scene_config

**parsing**
	processar e validar ficheiros .cub
	fluxo:
		parse_scene_file() → parse_configuration() → [texturas + cores] → map

