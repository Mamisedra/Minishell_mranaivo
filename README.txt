Ajout de t_env pour l'expansion :
	- Dans le propmpt de base.
	- Dans l'heredoc.
	- Dans Pipe.
	
La structure de t_env:

t_env:
	* Key (Une char* qui contient le nom du var ex : USER)
	* env_s (Une char* qui contient la contenu du var ou key)
	* next (C'est une pointeur vers la neoud suivant)
