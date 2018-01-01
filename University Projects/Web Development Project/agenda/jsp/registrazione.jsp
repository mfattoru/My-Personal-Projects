<!--
Java Server Page che si occupa dell'inserimento di un nuovo utente all'interno del database
Questa dopo aver ricevuto i dati dalla pagina registrazione.html ed aver inserito i dati
nel database crea direttamente una sessione con il server,simulando quindi anche il login 
dell'utente con gli stessi dati con cui si  iscritto
-->
<DOCTYPE html>
<%@ page import ="java.sql.*" %>
<%@ page import ="javax.sql.*" %>

<html>
  <head>
  </head>
  
  <body>
  
    <%
	//recupero dati dalla request
	String user=request.getParameter("userid"); 
	String pwd=request.getParameter("pwd"); 
	String fname=request.getParameter("fname"); 
	String lname=request.getParameter("lname"); 
	String email=request.getParameter("email"); 
	String indirizzo=request.getParameter("indirizzo");
	try{
	  //inizializzazione connessione al database
	  Class.forName("com.mysql.jdbc.Driver"); 
	  java.sql.Connection con = DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123"); 
	  Statement st= con.createStatement(); 
	  ResultSet rs; 
	  //inserimento dei dati all'interno del database
	  st.executeUpdate("insert into Utente (IdUtente,Password,Nome,Cognome,Email,Indirizzo) values ('"+user+"','"+pwd+"','"+fname+"','"+lname+"','"+email+"','"+indirizzo+"')");   
	  //creazione ed inizializzazione della sessione
	  session=request.getSession(true); 
	  session.setAttribute("userid",user);
	  String redirectURL = "../success/registrazione.html";
	  response.sendRedirect(redirectURL);
	}
	catch(Exception e){
	  String redirectURL = "../error/registrazione.html";
	  response.sendRedirect(redirectURL);
	}
     %>	
  
  </body>

  </head>
</html>