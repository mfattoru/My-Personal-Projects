<!--
Java Server Page che si occupa della partecipazione di un utente all'evento.
nel caso in cui l'utente sia registrato all'applicazione ma non ancora loggatogli viene consigliato 
di effettuare il login all'applicazione per una piùrapida iscrizione all'evento.
nel caso in cui l'utente sia registrato e loggato all'applicazione viene automaticamente iscritto all'evento.
nel caso in cui l'utente non sia registrato all'applicazione gli viene mostrato un form dove dovrà inserire 
i dati essenziali per la partecipazione all'evento.

-->
<html>
  <head>
    <title>Partecipa Evento</title>
    <%@ page import= "java.sql.*" %>
    <%@ page import= "javax.sql.*" %>
  </head>
  <body>
    <% 
      String Nome,Cognome,Email,Id;
      String IdEvento=request.getParameter("Id");
      try{
	//inizializzazione connessione al database
	Class.forName("com.mysql.jdbc.Driver"); 
	java.sql.Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123");
	Statement st= conn.createStatement();
      
	if(session.getAttribute("userid")!=null ){ //se l'utente è loggato
	  Id=(String)session.getAttribute("userid"); 
	  //recupero i dati dell'utente
	  ResultSet rs=st.executeQuery("select * from Utente where IdUtente= '"+Id+"'");
	  if(rs.next()){
	    Nome=rs.getString("Nome");
	    Cognome=rs.getString("Cognome");
	    Email=rs.getString("Email");
	    //controllo se l'utente sta già partecipando all'evento all'evento
	    rs=st.executeQuery("select * from PartecipaEvento where Email='" +Email+"' and IdEvento='"+IdEvento+"'");
	    if(!rs.next()){ //se l'utente non sta già partecipando all'evento lo iscrivo all'evento
	      st.executeUpdate("insert into PartecipaEvento (IdEvento,Nome,Cognome,IdUtente,Email) values("+IdEvento+",'"+Nome+"', '"+Cognome+"','"+Id+"','"+Email+"')");
	      %>
		<center>
		  Hai Confermato La Tua Partecipazione all'evento.Grazie Mille
		  <META HTTP-EQUIV="REFRESH" CONTENT="5; URL=../static/calendario.html">
		</center>
	      <%
	    }
	    else{//altrimenti gli mostro un messaggio che dice che è già iscritto all'evento
	      %>
		<center>
		  sei già iscritto all'evento
		  <META HTTP-EQUIV="REFRESH" CONTENT="5; URL=../static/calendario.html">
		</center>
	      <%
	    }
	  }
	}
	else{ //se l'utente non è loggato gli viene chiesto di loggare o di compilare una form per avere almeno i dati fondamentali per l'iscrizione
	  %>
	    <h1 align="center">Compila i seguenti campi per confermare la partecipazione all'evento:</h1>
	    <h3 align="center">Se sei iscritto al sito,effettua il login cliccando <a href="login.jsp">qui</a> e poi riapri la pagina</h3>
	    <form name="partecipaEvento" id="partecipaEvento" align="center" method="GET" action="partecipaevento.jsp">
	      <input type="hidden" name="Id" value="<%=IdEvento%>" >
	      <!--Nome (caratteri, lettere accentate apostrofo e un solo spazio fra le parole)-->
	      Nome:<input type="text" name="Nome" required pattern="^([a-zA-Z\xE0\xE8\xE9\xF9\xF2\xEC\x27]\s?)+$" title="caratteri, lettere accentate apostrofo e un solo spazio fra le parole"><br>
	      Cognome:<input type="text" name="Cognome" required pattern="^([a-zA-Z\xE0\xE8\xE9\xF9\xF2\xEC\x27]\s?)+$" title="caratteri, lettere accentate apostrofo e un solo spazio fra le parole"><br>
	      Email:<input type="text" name="Email" required pattern="^[a-zA-Z0-9._%-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$"><br>
	      <input type="submit" value="Partecipa Evento">
	    </form>
	  <%
	  if(request.getParameter("Email")!=null){ //se ha compilato il form precedente
	    Nome=request.getParameter("Nome");
	    Cognome=request.getParameter("Cognome");
	    Email=request.getParameter("Email");
	    //controllo se non esista nessuno iscritto con quella mail
	    ResultSet rs=st.executeQuery("select * from PartecipaEvento where Email='" +Email+"' and IdEvento='"+IdEvento+"'");
	    if(!rs.next()){  //se nessuno è iscritto con qella mail inserisco la partecipazione dell'utente
	      st.executeUpdate("insert into PartecipaEvento(IdEvento,Nome,Cognome,Email) values("+IdEvento+",'"+Nome+"', '"+Cognome+"','"+Email+"') ");
	       %>
		<center>
		  Hai Confermato La Tua Partecipazione all'evento.Grazie Mille
		</center>
	      <%
	    }
	    else{ //altrimenti mostro un messaggio per dire all'utente che è già iscritto all'evento
	      %>
		<center>
		  sei già iscritto all'evento
		</center>
	      <%
	    }
	  }
	}
      }
      catch(Exception e){
	%>
	  <center>
	    Non è Stato possibile farti partecipare all'evento.riprova più tardi
	  </center>
	<%
      }
    %>
  </body>

</html>