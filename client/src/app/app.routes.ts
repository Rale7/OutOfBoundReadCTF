import { Routes } from '@angular/router';
import { LoginComponent } from './components/login/login.component';
import { PasswordsComponent } from './components/passwords/passwords.component';
import { AuthGuard } from './guards/auth.guard';
import { LoginGuard } from './guards/login.guard';

export const routes: Routes = [
  { path: '', redirectTo: 'login', pathMatch: 'full' },
  { path: 'login', component: LoginComponent, canActivate: [LoginGuard] },
  { path: 'passwords', component: PasswordsComponent, canActivate: [AuthGuard] },
];
