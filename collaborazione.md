# Guida per collaborare al progetto Controllo Accessi Gulli

### :large_blue_circle: 1. Creare un account su  Github ( https://github.com/join )

### :large_blue_circle: 2. SW da scaricare sul proprio PC

- [Arduino IDE SW ] (https://www.arduino.cc/en/Main/Software)
- [Git - distributed version control system ] (https://git-scm.com/)

### :large_blue_circle: 3.  Clonare un progetto Github su Github
Dopo aver eseguito l'accesso con il proprio account Github cercare il repository principale di progetto *controllo_accessi_gulli* ed eseguire un **Fork** del repository.
Questo creerà una copia del repository sul proprio account Github. E' già possibile lavorare al progetto on-line andando a modificare i singoli file.
####  a. Fare il committ di un file modificato
Quando un file è stato modificato è possibile registrare le modifiche per creare una storia del progetto. Per farlo esiste il tasto **[ Commit Changes ]** in fondo all'editor. E' buona norma inserire un messaggio di commit per ricordarsi quali modifiche sono state fatte sul file.



### :large_blue_circle: 4. Clonare un progetto Github sul proprio PC
Dopo aver installato Git sul proprio PC posizionarsi nel file system dove si vuole che venga creata la directory di progetto.
Eseguire il comando: 
 `git clone https://github.com/git_hub_user_name/controllo_accessi_gulli`
Verrà creata una directory con il contenuto del progetto come esiste su Github nell'account personale creato all'inizio. Adesso è possibile lavorare in locale usando gli strumenti di sviluppo preferiti.
####    a. Fare il committ di un file modificato
Quando un file è stato modificato ed un piccolo progresso od obiettivo sono stati raggiunti si possono registrare le modifiche per creare una storia del progetto nel repository locale. Eseguire il comando:
`git commit -a -m "messaggio di commit"`

####    b. Aggiornare il proprio repository su Github con il lavoro fatto in locale
eseguire il comando `git push origin/master`. In questo modo il repository remoto sarà sincronizzato con quello locale


### :large_blue_circle: 5. Sincronizare il proprio repository remoto con il repository principlae di progetto entrambi su Github
Non è possibile farlo direttamente da Github ma bisogna passare attraverso il proprio repository locale sul PC
Per prima cosa aggiungere il repository principale di progetto come un altro repository remoto collegato al repository locale:

`git remote add upstream https://github.com/subakun/controllo_accessi_gulli` 

in questo modo abbiamo aggiunto un repository remoto con il nome *upstream*. Quando vogliamo sincronizzarci con il repository upstream (è meglio farlo spesso per non rimanere troppo indietro con gli aggiornamenti ) bisogna eseguire i seguenti comandi:

`git fetch upstream ( recupera una copia del repository remoto )`

`git rebase origin/master ( applica le variazioni al repository locale )`

adesso è necessario aggiornare il proprio repository su Github  con il comando:

`git push origin/master`

### :large_blue_circle: 6. Effettuare una Pull request
Quando è stato fatto del lavoro di sviluppo su una parte del codice e si desidera che questa venga  incorporata nel progetto principale e necessario eseguire l'operazione di **pull request** dal proprio account Github verso il repository di cui abbiamo fatto il Fork all'inizio (il repository principale di progetto). La pull request sarà fatta dopo che tutti i file modificati sono stati sottoposti a commit locale ed il proprio repository remoto è stato aggiornato con un comando di *push* (vedi 4.b)


https://help.github.com/articles/using-pull-requests/







un progetto Github sul proprio PC
Come sincronizzare un fork con server remoto upstream
http://stackoverflow.com/questions/7244321/how-do-i-update-a-github-forked-repository?lq=1





cose da installare

git
GitHub  desktop
IDE arduino
Python
ATOM
Platformio ecc. ecc.

[https://git-scm.com/book/en/v2/Git-Basics-Working-with-Remotes]

Come clonare un repository sul proprio PC locale per contribuire al progetto

Creare un proprio  account github ( git_hub_user_name & git_hub_password )

effettuare il Fork del progetto (icona)

clonare sul proprio PC locale il repository per lavorarci

git clone https://github.com/git_hub_user_name/controllo_accessi_gulli


lavorare al progetto prima direttamente su github 

poi fare un pull per sincronizzare il erpo locale

poi fare una modifica in locale

poi fare un push su repo remoto


Caricare le modifiche sul repo github

Fareuna pull request per incorporare le modifiche le repo di progetto



