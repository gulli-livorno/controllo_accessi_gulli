#!/usr/bin/env  python
# coding=utf-8
#*********************Python function  header******************************
__doc__="""make_html.py: Questa funzione stampa  una pagina html per visualizzare
i valori dei contatori di ingresso uscita ed un eventuale codice di errore in modo
che possano essere visualizzati in un browser"""
__author__ = "Stefano Baldacci"
__copyright__ = """Copyright information The content of this file is property of
Stefano Baldacci.It cannot be used, copied, modified, transferred or disclosed
without prior written agreement"""
__license__ = "GPL"
__email__ = "stefano.baldacci@gmail.com"
__status__ = "Production"
#History: (repeat the following line as many times as applicable)
__version__ = "0.1.1 original"
#******************************************************************************

def MakeHTML(InCounter, OutCounter,Status):
			VisCounter =InCounter-OutCounter
			html_page="""
			<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2//EN">
			<html>
			<head>
			<title>GUlli web_panel</title>
			</head>
			<body bgcolor=#B8EFE2 STYLE="background-color: #B8EFE2;">
			<h1 align="center">GULLI Controllo Accessi</h1>

			<h1 align="center">&nbsp;</h1>

			<h1 align="center">&nbsp;</h1>

			<table align="center" border="1" cellpadding="1" cellspacing="1" style="width: 500px">
				<tbody>
					<tr>
						<td>
						<p><span style="color: #00ff00"><span style="font-size: 72px"><span style="font-family: georgia,serif">INGRESSI</span></span></span></p>
						</td >
						<td width="150"><span style="font-size: 72px"><span style="font-family: georgia,serif">{InCounter}</span></span></td>
					</tr>
					<tr>
						<td>
						<p><span style="color: #ff8c00"><span style="font-size: 72px"><span style="font-family: georgia,serif">USCITE</span></span></span></p>
						</td >
						<td width="150"><span style="font-size: 72px"><span style="font-family: georgia,serif">{OutCounter}</span></span></td>
					</tr>
					<tr>
						<td ><span style="color: #0066ff"><span style="font-size: 48px"><span style="font-family: georgia,serif">VISITATORI PRESENTI</span></span></span></td>
						<td width="150"><span style="font-size: 72px"><span style="font-family: georgia,serif">{VisCounter}</span></span></td>
					</tr>
					<tr>
						<td><span style="font-size: 36px"><span style="font-family: georgia,serif">Stato</span></span></td>
						<td width="150"><span style="font-size: 36px">{Status}</span></td>
					</tr>
				</tbody>
			</table>
			</body>
			</html>
			"""

			print("Content-Type: text/html\n\n") #required HTTP header
			print(html_page.format(**locals())) # sostituisce i valori delle variabili tra { } nella stringa html_page
