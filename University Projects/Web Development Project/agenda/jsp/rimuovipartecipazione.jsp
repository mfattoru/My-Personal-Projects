<!--
Java Server Page che si occupa della rimozione della partecipazione di un utente da un evento
Questa si occupa della rimozione dal database della partecipazione dell'utente e successivamente
dell'invio al proprietario dell'evento di una mail che lo informa della non-partecipazione dell'utente
-->
<html>

  <head>
    <title>Rimuovi Partecipazione</title>
    <%@ page import= "java.sql.*" %>
    <%@ page import= "javax.sql.*" %>
    <%@ include file="../WEB-INF/template/sendMail.jsp" %>
  </head>
	
  <body>
  <%
    String Email;
    String Nome;
    String Cognome;
    String TestoMail;
    String NomeEvento;
    int del=1;
    try{
      if(session.getAttribute("userid")!=null){ // se l'utente è loggato
	//recupero dati dalla sessione e dalla request
	String user = (String)session.getAttribute("userid");
	String idevento = request.getParameter("Id");
	//inizializzazione connessione al database
	Class.forName("com.mysql.jdbc.Driver"); 
	java.sql.Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123"); 
	Statement st= conn.createStatement(); 
	//recupero la mail del proprietario dell'evento
	ResultSet rs=st.executeQuery("select Email from Evento join Utente on Proprietario = IdUtente where Id="+idevento);
	if(rs.next()){
	  Email=rs.getString(1);
	  rs.close();
	  //recupero il nome dell'evento a cui l'utente non vuole più partecipare
	  rs=st.executeQuery("select Nome From Evento where Id='"+ idevento+"'");
	  rs.next();
	  NomeEvento=rs.getString(1);
	  rs.close();
	  //recupero nome e cognome dell'utente che ha annullato la partecipazione all'evento
	  rs=st.executeQuery("select Nome,Cognome from Utente where IdUtente= '"+user+"'");
	   if(rs.next()){
	    Nome=rs.getString(1);
	    Cognome=rs.getString(2);
	    TestoMail="L'utente "+Cognome+" "+Nome+" ha abbandonato l'evento "+NomeEvento;
	   
	    //invio una mail al proprietario dell'evento avvisandolo che l'utente ha rimosso la partecipazione al suo evento
	  if(sendMail(Email," Rimozione Partecipazione",TestoMail)){
	    del=0;
	    %>
	    <center> &egrave stata inviata una mail al proprietario dell'evento per avvisarlo della tua non partecipazione all'evento </center>
	    <%
	  }
	  else{
	    %>
	    <center> non &egrave stato possibile inviare una mail al proprietario dell'evento per avvisarlo della tua non partecipazione all'evento.riprova più tardi </center>
	    <%
	  }
	 }
	
	}
	if(del==0){
	  //annullo la partecipazione all'evento da parte dell'utente
	  st.executeUpdate("delete from PartecipaEvento where IdEvento='"+idevento+"' and IdUtente= '"+user+"'");
	  %>
	  <center>
	    <p>Cancellazione Avvenuta Correttamente</p>
	  </center>
	  <%
	}
	%>
	<META HTTP-EQUIV="REFRESH" CONTENT="5; URL=../static/calendario.html">
	<%
      }
      else{ //redirezione alla pagina di login se l'utete non è loggato
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