<!--
Java server page che si occupa dell aggiornaento delle informazioni di un contatto
questa pagina riceve in ingresso l'indirizzo e-mail del contatto da modificare,elemento che
permette di identificare univocamente il contatto all'interno della rubrica dell'utente
sucessivamente riceve in ingresso dalla pagina modificacontatto.jsp tutti i dati da aggiornare
-->
<!DOCTYPE html>

<html>
  <head>
    <%@ page import="java.sql.*" %>
    <%@ page import="javax.sql.*" %>
  </head>
  
  <body>
    <%
      String Id;
      String Nome;	
      String Cognome;
      String Indirizzo;
      String Email;
      String Telefono;
      String OldEmail;
      try{
	if(session.getAttribute("userid")!=null){ //se l'utente è loggato
	  Id = (String)session.getAttribute("userid");
	  OldEmail= request.getParameter("OldEmail"); //variabile che mi serve per identificare l'utente nella rubrica
	  //inizializzazione connessione al database
	  Class.forName("com.mysql.jdbc.Driver"); 
	  java.sql.Connection con = DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123"); 
	  Statement st= con.createStatement();
	  //recupero dati dalla request
	  Nome=request.getParameter("Nome");
	  Cognome=request.getParameter("Cognome");
	  Indirizzo=request.getParameter("Indirizzo");
	  Email=request.getParameter("Email");
	  Telefono=request.getParameter("Telefono");
	  //aggiornamento contatto nella rubrica
	  st.executeUpdate("update Rubrica  set Nome= '"+Nome+"', Cognome='"+Cognome+"' , Indirizzo= '"+Indirizzo+"', Email= '"+Email+"' , Telefono= '"+Telefono+"' where Proprietario='"+Id+"' and Email='"+OldEmail+"'");
	
	  %>
	    <center>
	    <p>Inserimento Avvenuto Correttamente</p>
	    redirezione tra 5 secndi...
	    <META HTTP-EQUIV="REFRESH" CONTENT="5; URL=paginacontatto.jsp?Email=<%=Email%>">
	    </center>

	  <%
	}
	else{ //redirezione nel caso in cui l'utente non sia loggato
	  String redirectURL = "login.jsp";
	  response.sendRedirect(redirectURL);
	}
      }
      catch(Exception e){
	%>
	  <p align="center">errore durante l'aggiornamento...riprova più tardi</p>
	<%
      }
    %>
  </body>
</html>