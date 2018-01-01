<!--
Java Server Page che si occupa dell'inserimento di nuovi contatti nella rubrica.
questa pagina riceve dalla pagina aggiungirubrica.html ,la quale gestisce un form
per la richiesta dei dati da parte dell'utente ,i seguentiin parametri in ingresso:
nome,cognome,indirizzo E-mail,indirizzo e numero di telefono
-->

<html>
  <head>
    <%@ page import= "java.sql.*" %>
    <%@ page import= "javax.sql.*" %>
  </head>
  <body>
    <% 
      try{
	if(session.getAttribute("userid")!=null){ //se l'utente è loggato
	  //Recupero dati dalla request
	  String Proprietario = (String)session.getAttribute("userid");
	  String Nome = request.getParameter("Nome");
	  String Cognome = request.getParameter("Cognome");
	  String Email = request.getParameter("Email");
	  String Indirizzo = request.getParameter("Indirizzo");
	  String Telefono = request.getParameter("Telefono");
	  //inizializzazione connessione al database
	  Class.forName("com.mysql.jdbc.Driver"); 
	  java.sql.Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123"); 
	  Statement st= conn.createStatement(); 
	  //inserimento contatto nella rubrica
	  st.executeUpdate("insert into Rubrica(Nome,Cognome,Email,Indirizzo,Telefono,Proprietario) values ('"+Nome+"','"+Cognome+"', '"+Email+"' ,'"+Indirizzo+"','"+Telefono+"' ,'"+Proprietario+"')");
	  %>
	  <p align="center">Contatto Inserito correttamente.redirezione tra 5 secondi...</p>
	  <META HTTP-EQUIV="REFRESH" CONTENT="5; URL=rubrica.jsp">
	  <%
	}
	else{
	  String redirectURL = "login.jsp";
	  response.sendRedirect(redirectURL);
	}
      }
      catch(Exception e){ //in caso di errore rimanda l'utente alla homepage
      %>
	<p align="center">errore durante l'inserimento</p>

      <%
      }
    %>
  </body>

</html>