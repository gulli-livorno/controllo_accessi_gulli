#! python


import random
import make_html

INCounter= random.randint(1, 100)
OutCounter=random.randint(1, INCounter)
VisCoutner =INCounter-OutCounter
Status = ["OK", "Bloccata","Non risponde"]

make_html.MakeHTML(INCounter,OutCounter,random.choice(Status))
