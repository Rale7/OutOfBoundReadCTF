export interface Account {
  id?: number;
  service: string;
  username: string;
  password: string;
  email?: string;
  notes?: string;
}