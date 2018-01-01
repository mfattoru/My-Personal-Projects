<!--
Java Server Page che si occupa della cancellazione di un evento.
questa riceve in input l'id dell'evento,attributo che mi permette di 
identificare univocamente l'evento nel database
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
	String Id = (String)session.getAttribute("userid");
	String Email = request.getParameter("Email");
	//inizializzazione connessione al database
	Class.forName("com.mysql.jdbc.Driver"); 
	java.sql.Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123"); 
	Statement st= conn.createStatement(); 
	//cancellazione contatto dalla rubrica
	st.executeUpdate("delete from Rubrica where proprietario='"+Id+"' and email= '"+Email+"'");
	%>
	  <center>
	  <p>Cancellazione Avvenuta Correttamente</p>
	  redirezione tra 5 secondi...
	  <META HTTP-EQUIV="REFRESH" CONTENT="5; URL=rubrica.jsp">
	  </center>

	<%
      }
      else{ //redirezione in caso di utente non loggato
	String redirectURL = "login.jsp";
	response.sendRedirect(redirectURL);
      }
    }
    catch(Exception e){
    %>
      <p align="center">errore durante la cancellazione </p>
    <%
    }
  %>
  </body>

</html>