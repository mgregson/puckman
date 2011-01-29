all: runme

runme: basic_puckman
	cp basic_puckman runme

basic_puckman: *.ml
	ocamlfind ocamlc -package extlib -linkpkg basic_puckman.ml -o basic_puckman

clean:
	rm a.out basic_puckman basic_puckman.cmi basic_puckman.cmo
	rm -rf _build