<!--
Java Server Page per la gestione della modifica di un evento
La Server Page riceve in ingresso dalla pagina modificaevento.jsp 
tutti i nuovi dati da aggiornare e succesivamente invia una mail a tutti i
partecipanti all'evento per informarli dell'avvenuta modifica dell'evento
-->
<!DOCTYPE html>

<html>
  <head>
    <%@ page import="java.sql.*" %>
    <%@ page import="javax.sql.*" %>
    <%@ include file="../WEB-INF/template/sendMail.jsp" %>
  </head>
  
  <body>
    <%
      //dichiarazioni variabili
      String IdEvento;
      String OldNomeEvento="";
      String NomeEvento;
      String Data;
      String OraInizio;
      String OraFine;
      String Luogo;
      String Descrizione;  
      String prop;
      String Email="";
      String TestoMail;
      String tempMail;
      int update=1;
      int flag=1;
      try{
	if(session.getAttribute("userid")!=null){ //se l'utente è loggato
	  IdEvento = request.getParameter("Id");
	  //inizializzazione connessione al database
	  Class.forName("com.mysql.jdbc.Driver"); 
	  java.sql.Connection con = DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123"); 
	  Statement st= con.createStatement();
	  //recupero dati dalla request
	  NomeEvento=request.getParameter("NomeEvento");
	  Data=request.getParameter("Data");
	  OraInizio=request.getParameter("OraInizio");
	  OraFine=request.getParameter("OraFine");
	  Luogo=request.getParameter("Luogors.close();");
	  Descrizione=request.getParameter("Descrizione");
	  prop=(String)session.getAttribute("userid");
	  
	  ResultSet rs=st.executeQuery("select Nome from Evento where Id="+IdEvento);
	  if(rs.next()){
	    OldNomeEvento=rs.getString(1);
	  }
	  //recupero delle mail dei  partecipanto all'evento
	  rs=st.executeQuery("select Email from PartecipaEvento where IdEvento= "+IdEvento);
	  while(rs.next()){
	    flag=0;
	    tempMail=rs.getString(1)+",";
	    Email=Email+tempMail;
	  }
	  if(flag==0){ //se c'è almeno un partecipante,informali della modifica dell'evento
	    TestoMail="Gentile utente la avvertiamo che l'evento "+OldNomeEvento+" ha subito delle modifiche e la invitiamo a visitare la pagina: http://127.0.0.1:8080/agenda/jsp/paginaevento.jsp?Id="+IdEvento;  
	    if(sendMail(Email,"Evento Modificato",TestoMail)){  
	      update=0;
	      %>
	      <center>
	      <p>&egrave stata inviata una mail ad ogni partecipante all'evento per informarlo dei cambi avvenuti</p>
	      </center>
	      <%
	    }
	    else{
	      %>
	      <center>
	      <p>Non &grave stato possibile inviare una mail a tutti i partecipanti all'evento.riprova pi&ugrave tardi</p>
	      </center>
	      <%
	    }
	  }
	  if(update==0){ //aggiorno l'evento soltanto se sono riuscito a contattare tutti i partecipanti
	    //aggiornamento evento
	    st.executeUpdate("update Evento  set Nome= '"+NomeEvento+ "', Data='"+Data+"' , Descrizione= '"+Descrizione+"', OraInizio= '"+OraInizio+"' , OraFine= '"+OraFine+"' , Luogo= '"+Luogo+"' where Id= "+IdEvento);
	    %>
	    <center>
	      Aggiornamento dell'evento effettuato correttamente
	    </center>
	    <%
	  }
	  %>
	  <META HTTP-EQUIV="REFRESH" CONTENT="5; URL=paginaevento.jsp?Id=<%=IdEvento%>&mod=74910653">
	  <%
	}
	else{  //redirezione in caso di utente non loggato
	  String redirectURL = "login.jsp";
	  response.sendRedirect(redirectURL);
	}
      /
      catch(Exception e){
	%>
	  <p align="center">errore durante l'aggiornamento</p>
	<%
      }
    %>
  </body>
</html>