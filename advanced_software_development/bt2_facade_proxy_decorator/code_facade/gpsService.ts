export class GPSService {
  findRoute(start: string, end: string): string {
    return `GPS: Found a route from ${start} to ${end}`;
  }
}
