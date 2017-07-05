import { WorkCounterPage } from './app.po';

describe('work-counter App', () => {
  let page: WorkCounterPage;

  beforeEach(() => {
    page = new WorkCounterPage();
  });

  it('should display welcome message', () => {
    page.navigateTo();
    expect(page.getParagraphText()).toEqual('Welcome to app!!');
  });
});
