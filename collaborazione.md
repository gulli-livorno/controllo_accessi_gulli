# Guida per collaborare al progetto Controllo Accessi Gulli

### :white_small_square: 1. Creare un account su  Github ( https://github.com/join )

### :white_small_square: 2. SW da scaricare sul proprio PC

- [Arduino IDE SW ] (https://www.arduino.cc/en/Main/Software) (:raised_hand: chi ha già scritto e compilato almeno uno sketch su Arduino ce lo dovrebbe già avere )
- [Git - distributed version control system ] (https://git-scm.com/)
- [Una semlpice guida a Git ] (http://rogerdudler.github.io/git-guide/index.it.html)

### :white_small_square: 3.  Clonare un progetto Github su Github
Dopo aver eseguito l'accesso con il proprio account Github cercare il repository principale di progetto *controllo_accessi_gulli* ed eseguire un **Fork** del repository.
Questo creerà una copia del repository sul proprio account Github. E' già possibile lavorare al progetto on-line andando a modificare i singoli file anche se per lo sviluppo di SW non è opportuno lavorare direttamente sul repository on line ma è preferibile lavorare su una copia locale e poi aggiornare il repository remoto. Vedi punto 4.
####  a. Fare il **commit** di un file modificato
Quando un file è stato modificato è possibile registrare le modifiche per creare una storia del progetto. Per farlo esiste il tasto **[ Commit Changes ]** in fondo all'editor. E' buona norma inserire un messaggio di commit per ricordarsi quali modifiche sono state fatte sul file. Su Github per salvare le modifiche ad un file è comunque necessario fa un commit.



### :white_small_square: 4. Clonare un progetto Github sul proprio PC
Dopo aver installato Git sul proprio PC posizionarsi nel file system dove si vuole che venga creata la directory di progetto.
Eseguire il comando: 

 `git clone https://github.com/git_hub_user_name/controllo_accessi_gulli`
 
 dove *git_hub_user_name* è lo user name dell'account Github creato in precedenza.
Sarà creata una directory con il contenuto del progetto come esiste su Github nell'account personale creato all'inizio. Adesso è possibile lavorare in locale usando gli strumenti di sviluppo preferiti.
####    a. Fare il committ di un file modificato
Quando un file è stato modificato ed un piccolo progresso od obiettivo sono stati raggiunti si possono registrare le modifiche per creare una storia del progetto nel repository locale. Eseguire il comando:
`git commit -a -m "messaggio di commit"`

####    b. Aggiornare il proprio repository su Github con il lavoro fatto in locale
eseguire il comando `git push origin/master`. In questo modo il repository remoto sarà sincronizzato con quello locale (saranno richiesti user name e password del vostro account github per l'operazione di **push**)


### :white_small_square: 5. Sincronizare il proprio repository remoto con il repository principlae di progetto entrambi su Github
Non è possibile farlo direttamente da Github ma bisogna passare attraverso il proprio repository locale sul PC
Per prima cosa aggiungere il repository principale di progetto come un altro repository remoto collegato al repository locale:

`git remote add upstream https://github.com/subakun/controllo_accessi_gulli` 

in questo modo abbiamo aggiunto un repository remoto con il nome *upstream*. Quando vogliamo sincronizzarci con il repository upstream (è meglio farlo spesso per non rimanere troppo indietro con gli aggiornamenti ) bisogna eseguire i seguenti comandi:

`git fetch upstream ( recupera una copia del repository remoto )`

`git rebase origin/master ( applica le variazioni al repository locale )`

adesso è necessario aggiornare il proprio repository su Github  con il comando:

`git push origin/master`

### :white_small_square: 6. Effettuare una pull request
Quando è stato fatto del lavoro di sviluppo su una parte del codice e si desidera che questa venga  incorporata nel progetto principale e necessario eseguire l'operazione di **pull request** dal proprio account Github verso il repository di cui abbiamo fatto il Fork all'inizio (il repository principale di progetto). La pull request sarà fatta dopo che tutti i file modificati sono stati sottoposti a commit locale ed il proprio repository remoto è stato aggiornato con un comando di *push* (vedi 4.b). Dopo una pull request questa deve essere approvata dal proprietario del repository di progetto. Attraverso l'ambiente di Github è possibile scambiare  commenti e chiarimenti tra gli sviluppatori prima che il proprietario del repository approvi o rifiuti la pull request.

