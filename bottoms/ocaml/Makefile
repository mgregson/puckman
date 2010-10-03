all: basic_puckman

basic_puckman: *.ml
	ocamlc basic_puckman.ml && cp a.out basic_puckman

clean:
	rm a.out basic_puckman basic_puckman.cmi basic_puckman.cmo
	rm -rf _build