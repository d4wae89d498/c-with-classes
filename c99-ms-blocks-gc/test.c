globale 	(x, 0)
constante 	(hi, "lol")
locale		(pomme, 42)

classe 		(Bar,,
		entier y;
	,
	((entier x),
		printf ("Bar built\n");
		this->y = x;
		this->imprY();
	),
	(vide, imprY, (),
		printf ("Bar->y vaut %i\n", this->y);
	)
)


classe 		(Foo hérite de Bar,
		entier i;
	,
	((entier x),
		printf ("Foo built");
		this->i = x;
		super(x + 1);
		this->imprI();
	//	this->imprY();
	),
	(vide, imprI, (),
		printf ("Foo->i vaut %i\n", this->i);
	)
)

locale		(f, Foo_construct(1))


fonction (vide, name, (),
	si (1,

	)

	tant que (1,

	)

	retourner ;
)

fonction (vide, g, (),
	*x += 1;
)

exporter (g, x)
