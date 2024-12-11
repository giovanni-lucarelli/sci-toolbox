## Metodi da implementare
### funzioni dataframe
- copy assignment (?)
- mettere i metodi nel posto giusto (pubblici, privati)
- !!! [ ] classification (knn, tree?)

## main.cpp per analisi
- [x] percorso file input/output
- [x] scrivere su file output
- [x] accettare filename i/o da terminale

## final check
- [x] const correctness di tutti i metodi (const prima e dopo?)
- testare con il compilatore online (?)
- [x] scrivere tutti i runtime error e invalid argument etc
- [x] il comportamento degli optional è corretto in ogni metodo? std::nullopt
    - la media e tutte le altre come trattano i nullopt????

## build and structure
- [x] strutturare in cartelle
- [x] header
- row iterator in un altro file (?) 
- [x] source 
- [x] main
- [x] aggiornare cmake con boost!!!!!!!!!!!!!!!!!!!!!
- [x] libreria .so
- [x] linkare tutte le dependencies
- creare libreria con elena, compilabile separatamente!

## scrivere README.md
- guida installazione librerie terze parti
    - gls
    - boost
- guida cmake
- guida uso del toolbox
- struttura delle cartelle
- riscrivere tutti i commenti al codice
- controllare gestione errori nel codice


# Timeline

## Dec 9
- [x] aggiustare iteratore (pushback complicati inutilmente)
- [x] read_json(): cast di nullopt, string e double
- [x] read_csv(): cast di nullopt, string e double
- [x] scrivere count_nan()
- [x] comportamento delle funzioni del dataframe sui nullopt (?)
- [x] per usare cov e corr: devono avere la stessa dimensione => 
    - [x] drop riga nan
    - [x] drop col nan
- [x] aggiornare CMakeLists.txt e linkare tutto correttamente
- [x] scrivere stat_app.cpp per scrivere su file!

## Dec 10
- [x] scrivere main file per test
    - [x] metodo di summary
- [ ] scrivere documentazione
    - [ ] commenti codice solo su hpp
    - [ ] readme.md
- [ ] scrivere metodo di classificazione (?)
- [ ] mettere insieme la libreria con quella di elena
- [x] creare un metodo che calcola maximum width delle colonne per printare
- [x] throw error in table, cov corr, corr matrix se metto un categorico
- [x] modify the error messages!!!
