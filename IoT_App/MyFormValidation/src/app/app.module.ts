import { NgModule, ErrorHandler } from '@angular/core';
import { IonicApp, IonicModule, IonicErrorHandler } from 'ionic-angular';
import { MyApp } from './app.component';
import { HomePage } from '../pages/home/home';
import { ThankYouPage } from '../pages/thankyou/thankyou';
import { MyFormService } from '../services/myform';



@NgModule({
  declarations: [
    MyApp,
    HomePage,
	ThankYouPage
  ],
  imports: [
    IonicModule.forRoot(MyApp)
  ],
  bootstrap: [IonicApp],
  entryComponents: [
    MyApp,
    HomePage,
	ThankYouPage
  ],
  providers: [ /*{provide: ErrorHandler, useClass: IonicErrorHandler}*/ MyFormService]
})
export class AppModule {}
