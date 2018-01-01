<!--
Java Server Page che si occupa della gestione del logout dell'utente
-->
<DOCTYPE html>
<html>
  <head>

  </head>
  
  <body>
    <%
      if(session.getAttribute("userid")!=null){ // se l'utente è loggato effettuo il logout e lo redirigo alla homepage
        session.removeAttribute("userid"); 
        session.invalidate();
    %>
	Logout Effettuato Correttamente,sarai reindirizzato alla homepage
	<META HTTP-EQUIV="REFRESH" CONTENT="5; URL=../index.jsp">
    <%
      }
      else{ //altrimenti lo redirigo direttamente alla homepage
    %>
	Non Sei Loggato,Sarai reindirizzato alla homepage
	<META HTTP-EQUIV="REFRESH" CONTENT="5; URL=../index.jsp">
    <%
      }
    %>
  </body>
</html>