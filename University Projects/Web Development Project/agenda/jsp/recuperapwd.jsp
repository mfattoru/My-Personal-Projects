<!--
Java Server Page che si occupa del recupero della password dell'utente in caso di password dimenticata.
l'utente avrà a disposizione un form in cui dovrà inserire il nome utente con cui si è registrato.
in questo modo andremo a controllare la presenza dell'utente nel database.se la ricerca ha esito 
positivo viene inviata una mail all'utente contenente la password associata al suo account
-->
<html>

    <head>
	<title>Recupero Password</title>
	<%@ page import ="java.sql.*" %>
	<%@ page import ="javax.sql.*" %>
	<!--Includo pagina server per l'invio di mail-->
	<%@ include file="../WEB-INF/template/sendMail.jsp" %>
    </head>
    
    <body>
	<form name="recuperaPwd" id="recuperaPwd" action="recuperapwd.jsp" method="GET" align="center">
	    <h2 align="center">Inserisci il tuo nome utente per recuperare la tua password</h2><br>
	    User Name : <input type="text" name="user" required pattern="^([a-zA-Z0-9\.\_\-])+$">
	    <input type="submit" value="Recupera" />
	</form>
	
	<%
	    String user;
	    String email;
	    String pwd;
	    String mitt = "staffagenda2012@gmail.com";
	    //se è stato compilato il form di recupero password
	    if( (user = request.getParameter("user") ) != null){
		//inizializzo la connessione al database
		Class.forName("com.mysql.jdbc.Driver"); 
		java.sql.Connection con = DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123"); 
		Statement st= con.createStatement(); 
		//recupero mail e password dell'utente
		ResultSet rs=st.executeQuery("select email, Password from Utente where IdUtente='"+user+"'");
		if(rs.next()){ //se esiste un utente con quel nickname gli invio una mail sulla casella di posta con cui si è registrato al sito
		    email = rs.getString(1);
		    pwd = rs.getString(2);
		    if(sendMail(email,"Recupero Password","La tua vecchia Password e': "+pwd)){	    
		    %>

			<p align="center">ti &egrave stata inviata una mail contenente la tua password</p> 

		    <%	
		    }
		    else{
		    %>
			<p align="center">Impossibile Inviare la Mail...Riprova più Tardi</p>
		    <%
		    }
		}
		else{//se l'utente non esiste
	%>
		    <p align="center">nome utente non trovato</p>
	<%	}
		
	    }
	%>
    </body>

</html>