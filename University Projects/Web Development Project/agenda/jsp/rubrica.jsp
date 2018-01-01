<!--
Java Server Page che si occupa della generazione della rubrica dell'utente
questa recupera dalla sessione dell'id dell'utente per poi recuperare tutti i contatti dell'utente
da database.successivamente crea una tabella contenente tutti i contatti dell'utente.ogni contatto 
sarà cliccabile e ci redirezionerà alla visualizzazione dei dettagli del contatto
-->
<!DOCTYPE html>

<html>
	<head>
	  <title>Rubrica</title>
	  <%@ page import = "java.sql.*"%>
	  <%@ page import = "javax.sql.*"%>
	</head>
	<body>
	  <%
	    String Nome;
	    String Cognome;
	    String Id;
	    String Email;
	    
	    try{
	     
	      if(session.getAttribute("userid")!=null){ //controllo se l'utente è loggato
		  Id=(String)session.getAttribute("userid");
		  //inizializzazione connessione al database
		  Class.forName("com.mysql.jdbc.Driver");
		  java.sql.Connection con=DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123");
		  Statement st=con.createStatement();
		  //recuper di tutti i contatti salvati nella rubrica dell'utente
		  ResultSet rs=st.executeQuery("select Nome,Cognome,Email from Rubrica where proprietario= '"+Id+"'" );
		  %>
		  <center>
		  <table width=400 border=2 aling=center>
		    <tr>
			<h1>Rubrica</h1>
		    </tr>
		 <%
		  while(rs.next()){
		    Nome=rs.getString(1);
		    Cognome=rs.getString(2);
		    Email=rs.getString(3);
		  %>
	    
		  <tr>
		    <!-- creazione della tabella con link al profilo del contatto-->
		    <td>  <center> <a href="paginacontatto.jsp?Email=<%= Email %>" >  <%= Nome %> <%= Cognome %> </a>   </center></td>
		  </tr>
		  <%
		  }
		  %>
		  </table>
		  <%
	      }
	      else{ //redirezione alla pagina di login se l'utente non è loggato
		String redirectURL = "login.jsp";
		response.sendRedirect(redirectURL);
	      }
	   }
	   catch(Exception e){
	      %>
		<p align="center">errore durante la visualizzazione della rubrica</p>
	      <%  
	   }
	   
	 %>
	 <br>
	 <!--bottomi per l'aggiunta di un contatto e per il ritorno alla homepage del sito-->
	 <button name="nome" onclick="location.href='../static/aggiungirubrica.html'">Aggiungi Contatto</button>
	  <button name="nome" onclick="location.href='../static/calendario.html'">Home Page</button>
	 </center>
	  </body>
</html>
