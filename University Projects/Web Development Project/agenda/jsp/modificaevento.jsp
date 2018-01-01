<!--
Java Server Page che si occupa della modifica della richiesta all'utente dei campi da modificare
tramite una form.questa form avrà i campi imput-text già compilato,con i valori attualmente presenti sul database.
l'utente quindi portà modificare a duo piacere i dati.dopo aver effettuato la submit quindi
questi dati verranno inviati alla server page  aggiornaevento.jsp che si occuperà dell'eggiornamento delle informazione nel database
-->
<!DOCTYPE html>

<html>
  <head>
    <title>Modifica Evento</title>
    <%@ page import="java.sql.*" %>
    <%@ page import="javax.sql.*" %>
    <!--Inclusione script per il controllo della correttezza dell'inserimento dell'ora di inizio e di fine dell'evento
    in modo tale da non avere mai l'ora di fine precedente all'ora di inizio-->
    <SCRIPT type="text/javascript" SRC="../script/checkOra.js"></SCRIPT>
  </head>
  <body>
    <%
      //dichiarazione Variabili
      String Id;
      String NomeEvento;
      String Data;
      String OraInizio;
      String OraFine;
      String Luogo;
      String Descrizione;
      try{
	if(session.getAttribute("userid")!=null){   //controllo sulla sessione dell'utente.se l'utente è loggato
	  if( (Id = (String)request.getParameter("Id") ) != null){  //nel caso in cui sia selezionato un evento
	    //inizializzazione connessione al database
	    Class.forName("com.mysql.jdbc.Driver");
	    java.sql.Connection con = DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123");
	    Statement st=con.createStatement();
	    //recupero tutte le informazioni sull'evento
	    ResultSet rs=st.executeQuery("select * from Evento where Id= '"+Id+"'");
	    //se l'evento esiste nel database
	    if(rs.next()){
	      NomeEvento=rs.getString("Nome");
	      Data=rs.getString("Data");
	      OraInizio=rs.getString("OraInizio");
	      OraFine=rs.getString("OraFine");
	      Luogo=rs.getString("Luogo");
	      Descrizione=rs.getString("Descrizione");
	      %>
	      <!--Form precompilata contenente i dati correnti dell'evento.qui l'utente potra modificare i campi dell'evento.
	      se i campi delle form rispettano i pattern allora il tutto sarà inviato alla pagina server aggiornaevento.jsp che 
	      si preoccuperà di effettuare l'aggiornamento dei dati-->
	      <form name="checkOra"  id="checkOra" align="center" method="POST" action="aggiornaevento.jsp" onSubmit="return controllo();">
		<input type="hidden" name="Id" value="<%=Id%>" >
		<!--NomeEvento (caratteri,numeri, lettere accentate apostrofo e un solo spazio fra le parole)-->
		Nome Evento:<input type="text" name="NomeEvento" value="<%=NomeEvento%>" required pattern="^([a-zA-Z0-9\xE0\xE8\xE9\xF9\xF2\xEC\x27]\s?)+" title="caratteri,numeri, lettere accentate apostrofo e un solo spazio fra le parole"><br>
		<!--accetta date nel formato AAAA-MM-GG tra il 1900-01-01 e il 2099-12-31-->
		Data (AAAA-MM-GG):<input type="text" name="Data"  value="<%=Data%>" required pattern="^(19|20)\d\d[- /.](0[1-9]|1[012])[- /.](0[1-9]|[12][0-9]|3[01])$" title="accetta date nel formato AAAA-MM-GG tra il 1900-01-01 e il 2099-12-31"><br>
		<!--ora (accetta ore tra 0 e 24 con una o 2 cifre, minuti e secondi da 0 a 60 con una o due cifre e come separatore : )-->
		Ora Inizio:<input type="text" name="OraInizio" value= "<%=OraInizio%>" required pattern="^(([0-1]?[0-9])|(2[0-4]))((:)[0-6]?[0-9])+$" title="accetta ore tra 0 e 24 con una o 2 cifre, minuti e secondi da 0 a 60 con una o due cifre e come separatore : "><br>
		Ora Fine:<input type="text" name="OraFine" value="<%=OraFine%>" required pattern="^(([0-1]?[0-9])|(2[0-4]))((:)[0-6]?[0-9])+$" title="accetta ore tra 0 e 24 con una o 2 cifre, minuti e secondi da 0 a 60 con una o due cifre e come separatore : "><br>
		<!--Luogo,(caratteri,numeri,virgola, lettere accentate ,apostrofo e un solo spazio fra le parole)-->
		Luogo:<input type="text" name="Luogo"  value="<%=Luogo%>" required pattern="^([a-zA-Z0-9\ \xE0\xE8\xE9\xF9\xF2\xEC\x27,])+$" title="caratteri,numeri,virgola, lettere accentate apostrofo e un solo spazio fra le parole"><br>
		Descrizione:<input type="text" name="Descrizione" value="<%=Descrizione%>" > <br> <br>
		<input type="submit" value="Modifica Evento">
		<input type="reset" value="Cancella campi">
	      </form>
	      <%
	    }
	  }
	  else{//in caso di richiesta compilata on modo anomalo,ovvero senza la presenza di un id,redirezioniamo l'utente alla homepage
	    String redirectURL = "../static/calendario.html";
	    response.sendRedirect(redirectURL);
	  }
	}
	else{  //redirezione alla pagina di login nel caso in cui l'utente non sia lggato
	  String redirectURL = "login.jsp";
	  response.sendRedirect(redirectURL);
	}
      }
      catch(Exception e){
	%>
	  <p alicg="center">Errore Durante La Modifica</p>
	<%
      }
    %>
  </body>
</html>